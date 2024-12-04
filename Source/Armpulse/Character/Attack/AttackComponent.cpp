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

void UAttackComponent::ExecuteAttack(FVector HitboxSpawnLocation, FCollisionShape AttackHitbox, FRotator AttackRotation, float AttackAnimationLockTime, float ProcessAttackAfterAnimationTime)
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

        if (Damage < 0.0f)
        {
            Damage = 0.0f;
        }
        FQuat HitboxRotation = AttackRotation.Quaternion();
        
        // Define collision parameters and check for overlaps
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(OwnerCharacter); // Ignore self in overlap check

        if (AttackMontage)
        {
            OwnerCharacter->ExecuteMontage(AttackMontage, true, AttackAnimationLockTime);
        }

        FTimerHandle AttackTimer;
        FTimerDelegate AttackFunction;
        AttackFunction.BindLambda([=, this]()
        {
            // Check for enemies within the hitbox
            TArray<FOverlapResult> OverlapResults;
            bool bOverlap = GetWorld()->OverlapMultiByChannel(
                OverlapResults,
                HitboxSpawnLocation,
                HitboxRotation,
                ECC_GameTraceChannel1,
                AttackHitbox,
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
        });
        GetWorld()->GetTimerManager().SetTimer(AttackTimer, AttackFunction, ProcessAttackAfterAnimationTime, false);

        // Check for enemies within the hitbox
        // TArray<FOverlapResult> OverlapResults;
        // bool bOverlap = GetWorld()->OverlapMultiByChannel(
        //     OverlapResults,
        //     HitboxSpawnLocation,
        //     HitboxRotation,
        //     ECC_GameTraceChannel1,
        //     AttackHitbox,
        //     CollisionParams
        // );

        // if (bOverlap)
        // {
        //     for (FOverlapResult& Overlap : OverlapResults)
        //     {
        //         if (AActor* OverlapActor = Overlap.GetActor())
        //         {
        //             // Apply damage or other effects
        //             UE_LOG(LogTemp, Warning, TEXT("Overlap: %s"), *OverlapActor->GetName());
        //             UGameplayStatics::ApplyDamage(OverlapActor, Damage, OwnerInstigator, OwnerActor, DamageTypeClass);
        //         }
        //     }
        // }

        float GameTime = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Display, TEXT("%f"), GameTime);

    }
}