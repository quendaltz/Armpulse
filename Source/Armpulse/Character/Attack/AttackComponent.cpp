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

void UAttackComponent::ExecuteAttack(FVector HitboxSpawnLocation, float AttackAnimcationLockTime)
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
        
        FVector HitboxSize = FVector(TargetHitboxRadius, TargetHitboxRadius, 0.0f);
        FCollisionShape Hitbox = FCollisionShape::MakeBox(HitboxSize);
        FQuat HitboxRotation = AttackRotation.Quaternion();
        
        // Define collision parameters and check for overlaps
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(OwnerCharacter); // Ignore self in overlap check

        if (AttackMontage)
        {
            OwnerCharacter->ExecuteMontage(AttackMontage, true, AttackAnimcationLockTime);
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

        DrawDebugBox(GetWorld(), HitboxSpawnLocation, HitboxSize, HitboxRotation, FColor::Green, false, 1.0f); // Duration is 1 second

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

        float GameTime = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Display, TEXT("%f"), GameTime);

    }
}