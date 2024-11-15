#include "SwordRushSkill.h"

#include "../../Character/GameCharacter.h"
#include "../../Components/CharacterStatusComponent.h"

#include "GameFramework/Actor.h"

void USwordRushSkill::ActivateSkill(AGameCharacter* Instigator)
{
    if (Instigator)
    {
        float RushMultiplier = 0.8f; // 240% rush damage
        float RushHit = 3.0f; // 3 hits
        float RushDistance = 13.0f;

        float CharacterAttackPower = 0.0f;
        auto DamageTypeClass = UDamageType::StaticClass();
        CharacterAttackPower = Instigator->GetStatusComponent()->GetAttackPower();
        if (CharacterAttackPower < 0.0f)
        {
            CharacterAttackPower = 0.0f;
        }

        float SkillDamage = CharacterAttackPower * RushMultiplier;

        // FVector ActorLocation = OwnerActor->GetActorLocation();
        // FVector RightVector = OwnerActor->GetActorRightVector();
        // UE_LOG(LogTemp, Log, TEXT("AttackRotation %s"), *AttackRotation.ToString());
        // UE_LOG(LogTemp, Log, TEXT("RightVector %s"), *RightVector.ToString());

        FVector HitboxSpawnLocation = Instigator->GetForwardCharacterLocation(TargetHitboxRadius);
        FRotator AttackRotation = Instigator->GetActorRotation();
        
        FVector HitboxSize = FVector(TargetHitboxRadius, RushDistance, 0.0f);
        FCollisionShape Hitbox = FCollisionShape::MakeBox(HitboxSize);
        FQuat HitboxRotation = AttackRotation.Quaternion();
        
        // Define collision parameters and check for overlaps
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(Instigator); // Ignore self in overlap check

        if (AttackMontage)
        {
            Instigator->ExecuteMontage(AttackMontage);
        }

        OwnerCharacter->GetDashComponent()->StartDash();
        FVector CharacterTargetLocation = OwnerCharacter->GetForwardCharacterLocation(ActorCapsuleRadius + TargetHitboxRadius * 2);
        OwnerCharacter->SetActorLocation(CharacterTargetLocation, true);

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
                    UGameplayStatics::ApplyDamage(OverlapActor, SkillDamage, OwnerInstigator, OwnerActor, DamageTypeClass);
                }
            }
        }
    }
}