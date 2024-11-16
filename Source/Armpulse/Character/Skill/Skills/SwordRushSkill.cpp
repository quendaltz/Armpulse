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
    // static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageAsset(TEXT("/Game/Characters/Kwang/Montages/SwordRush_Montage"));
    // if (MontageAsset.Succeeded())
    // {
    //     SwordRushMontage = MontageAsset;.Object;
    // }
}

void USwordRushSkill::ActivateSkill(AGameCharacter* Instigator, AController* InstigatorController)
{
    if (!Instigator) return;

    // skill properties
    float RushMultiplier = 0.8f; // 240% rush total damage
    float RushHit = 3.0f; // 3 hits
    float RushDistance = 200.0f;
    float RushSpeed = 1000.0f;

    auto DamageTypeClass = UDamageType::StaticClass();
    float CharacterAttackPower = 0.0f;
    CharacterAttackPower = Instigator->GetStatusComponent()->GetAttackPower();
    float TargetHitboxRadius = 0.0f;
    TargetHitboxRadius = Instigator->GetCapsuleComponent()->GetScaledCapsuleRadius();
    if (CharacterAttackPower < 0.0f)
    {
        CharacterAttackPower = 0.0f;
    }

    float SkillDamage = CharacterAttackPower * RushMultiplier;

    FRotator AttackRotation = Instigator->GetActorRotation();
    FVector HitboxSpawnLocation = Instigator->GetForwardCharacterLocation(TargetHitboxRadius);
    
    FVector HitboxSize = FVector(TargetHitboxRadius * 2, RushDistance, 0.0f);
    FCollisionShape Hitbox = FCollisionShape::MakeBox(HitboxSize);
    FQuat HitboxRotation = AttackRotation.Quaternion();
    
    // Define collision parameters and check for overlaps
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Instigator); // Ignore self in overlap check

    if (SwordRushMontage)
    {
        Instigator->ExecuteMontage(SwordRushMontage);
    }

    Instigator->GetDashComponent()->StartDash(RushDistance, RushSpeed);
    FVector CharacterTargetLocation = Instigator->GetForwardCharacterLocation(TargetHitboxRadius * 2);
    Instigator->SetActorLocation(CharacterTargetLocation, true);

    DrawDebugBox(GetWorld(), HitboxSpawnLocation, HitboxSize, HitboxRotation, FColor::Green, false, 1.0f); // Duration is 1 second

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
}