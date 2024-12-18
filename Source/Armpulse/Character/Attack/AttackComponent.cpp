// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "Engine/OverlapResult.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"

#include "../Character/GameCharacter.h"
#include "../Components/CharacterStatusComponent.h"

#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackComponent::ExecuteAttack(float AttackDuration)
{
    AActor* OwnerActor = GetOwner();
    AGameCharacter* OwnerCharacter = nullptr;
    AController* OwnerInstigator = nullptr;
    if (OwnerActor)
    {
        OwnerCharacter = Cast<AGameCharacter>(OwnerActor);
        OwnerInstigator = OwnerActor->GetInstigatorController();
    }

    if (OwnerCharacter)
    {
        float Damage = 0.0f;
        auto DamageTypeClass = UDamageType::StaticClass();
        Damage = OwnerCharacter->GetStatusComponent()->GetAttackPower();

        float ActorCapsuleRadius = 0.0f;
        ActorCapsuleRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
        float TargetHitboxRadius = 0.0f;
        TargetHitboxRadius = OwnerCharacter->GetStatusComponent()->GetAttackRadius();

        if (TargetHitboxRadius < 0.0f)
        {
            return;
        }

        if (Damage < 0.0f)
        {
            Damage = 0.0f;
        }

        FRotator AttackRotation = OwnerCharacter->GetActorRotation();
        FVector HitboxSpawnLocation = OwnerCharacter->GetForwardCharacterLocation(ActorCapsuleRadius + TargetHitboxRadius);
        
        FVector HitboxSize = FVector(TargetHitboxRadius, TargetHitboxRadius, 0.0f);
        FCollisionShape Hitbox = FCollisionShape::MakeBox(HitboxSize);
        FQuat HitboxRotation = AttackRotation.Quaternion();
        
        // Define collision parameters and check for overlaps
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(OwnerCharacter); // Ignore self in overlap check

        if (AttackMontage)
        {
            OwnerCharacter->ExecuteMontage(AttackMontage, true, AttackDuration);
        }

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
                    UGameplayStatics::ApplyDamage(OverlapActor, Damage, OwnerInstigator, OwnerActor, DamageTypeClass);
                }
            }
        }
    }
}