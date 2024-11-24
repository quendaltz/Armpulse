#include "SwordRushSkill.h"

#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"

#include "../../Character/GameCharacter.h"
#include "../../Components/CharacterStatusComponent.h"
#include "../../Components/Movement/CharacterDashComponent.h"

#include "GameFramework/Actor.h"

USwordRushSkill::USwordRushSkill()
{
    SkillName = "Sword Rush";
    ActionLockTime = 2.2f;
    CooldownTime = 7.0f;
}

void USwordRushSkill::ActivateSkill(AGameCharacter* Instigator, AController* InstigatorController)
{
    if (!Instigator) return;

    UCharacterStatusComponent* CharacterStatusComponent = Instigator->GetStatusComponent();

    // skill properties
    float RushMultiplier = 0.8f; // 240% rush total damage
    float RushHit = 3.0f; // 3 hits
    float RushDistance = 400.0f;
    float RushSpeed = 3000.0f;
    float ChargeStartTime = 0.04f; // before dash
    float ChargeDuration = 1.26f;
    float DashDuration = 0.2f;
    float EndDuration = 0.6f;

    auto DamageTypeClass = UDamageType::StaticClass();
    float CharacterAttackPower = 0.0f;
    CharacterAttackPower = CharacterStatusComponent->GetAttackPower();
    float TargetHitboxRadius = 0.0f;
    TargetHitboxRadius = CharacterStatusComponent->GetAttackRadius();

    if (TargetHitboxRadius < 0.0f)
    {
        return;
    }

    if (CharacterAttackPower < 0.0f)
    {
        CharacterAttackPower = 0.0f;
    }

    float SkillDamage = CharacterAttackPower * RushMultiplier;
    UE_LOG(LogTemp, Display, TEXT("Cal: %f, %f, %f"), CharacterAttackPower, RushMultiplier, SkillDamage);

    FRotator AttackRotation = Instigator->GetActorRotation();
    FVector HitboxSpawnLocation = Instigator->GetForwardCharacterLocation(RushDistance / 2.0f);
    
    FVector HitboxSize = FVector(TargetHitboxRadius, RushDistance / 2.0f, 0.0f);
    FCollisionShape Hitbox = FCollisionShape::MakeBox(HitboxSize);
    FQuat HitboxRotation = AttackRotation.Quaternion();
    
    // Define collision parameters and check for overlaps
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Instigator); // Ignore self in overlap check

    if (SwordRushMontage)
    {
        float AnimationTimeMultipiler = ActionLockTime / SwordRushMontage->GetPlayLength();

        Instigator->ExecuteMontage(SwordRushMontage); // play as default 1x rate

        FTimerHandle StartChargeTimer;
        FTimerDelegate StartChargeFunction;
        StartChargeFunction.BindLambda([this, Instigator, ChargeDuration]()
        {
            //UE_LOG(LogTemp, Display, TEXT("0.5f"));
            Instigator->SetMontagePlayRate(SwordRushMontage, 0.02f/ChargeDuration);
        });

        FTimerHandle ReleaseChargeTimer;
        FTimerDelegate ReleaseChargeFunction;
        ReleaseChargeFunction.BindLambda([this, Instigator, DashDuration]()
        {
            //UE_LOG(LogTemp, Display, TEXT("0.4f ?? 0.9f"));
            Instigator->SetMontagePlayRate(SwordRushMontage, 0.32f/DashDuration);
        });

        FTimerHandle EndTimer;
        FTimerDelegate EndFunction;
        EndFunction.BindLambda([this, Instigator, EndDuration]()
        {
            Instigator->SetMontagePlayRate(SwordRushMontage, 0.82f/EndDuration);
        });

        // animation 1.2 secs > swing 0.04 / charge 0.04 > 0.06 / dash 0.06 > 0.38 / end 0.38 > 1.20
        // desire 2 secs > swing 0.04 / charge 1.26 / dash 0.2 / end 0.6

        // holysht SetTimer is not await function :/
        GetWorld()->GetTimerManager().SetTimer(StartChargeTimer, StartChargeFunction, ChargeStartTime, false); // start charge
        GetWorld()->GetTimerManager().SetTimer(ReleaseChargeTimer, ReleaseChargeFunction, ChargeStartTime + ChargeDuration, false); // start dash
        GetWorld()->GetTimerManager().SetTimer(EndTimer, EndFunction, ChargeStartTime + ChargeDuration + DashDuration, false); // attack end
    }

    FTimerHandle StartDashTimer;
    FTimerDelegate StartDashFunction;
	StartDashFunction.BindLambda([Instigator, RushDistance, RushSpeed]()
	{
		Instigator->GetDashComponent()->StartDash(RushDistance, RushSpeed);
	});
    // ChargeStartTime + ChargeDuration = Start Dash
    GetWorld()->GetTimerManager().SetTimer(StartDashTimer, StartDashFunction, ChargeStartTime + ChargeDuration, false);

    FTimerHandle DashAttackTimer;
    FTimerDelegate DashAttackFunction;
	DashAttackFunction.BindLambda([=, this]()
	{
        // Check for enemies within the hitbox
		TArray<FOverlapResult> OverlapResults;
        bool bOverlap = GetWorld()->OverlapMultiByChannel(
            OverlapResults,
            HitboxSpawnLocation,
            HitboxRotation,
            ECC_GameTraceChannel1,
            Hitbox,
            CollisionParams
        );

        if (bOverlap)
        {
            for (FOverlapResult& Overlap : OverlapResults)
            {
                if (AActor* OverlapActor = Overlap.GetActor())
                {
                    // Apply damage or other effects
                    UE_LOG(LogTemp, Warning, TEXT("Overlap: %s"), *OverlapActor->GetName());
                    UGameplayStatics::ApplyDamage(OverlapActor, SkillDamage, InstigatorController, Instigator, DamageTypeClass);
                }
            }
        }

        DrawDebugBox(GetWorld(), HitboxSpawnLocation, HitboxSize, HitboxRotation, FColor::Green, false, 1.0f); // Duration is 1 second
	});
    GetWorld()->GetTimerManager().SetTimer(DashAttackTimer, DashAttackFunction, ChargeStartTime + ChargeDuration + DashDuration, false);
}