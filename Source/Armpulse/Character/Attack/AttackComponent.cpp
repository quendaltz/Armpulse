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

void UAttackComponent::ExecuteAttack()
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

        // FVector ActorLocation = OwnerActor->GetActorLocation();
        // FVector RightVector = OwnerActor->GetActorRightVector();
        // UE_LOG(LogTemp, Log, TEXT("AttackRotation %s"), *AttackRotation.ToString());
        // UE_LOG(LogTemp, Log, TEXT("RightVector %s"), *RightVector.ToString());

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
            UE_LOG(LogTemp, Log, TEXT("ExecuteMontage"));
            OwnerCharacter->ExecuteMontage(AttackMontage);
            //OwnerCharacter->ExecuteAnimation(AttackAnimation);
        }
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
                    UGameplayStatics::ApplyDamage(OverlapActor, Damage, OwnerInstigator, OwnerActor, DamageTypeClass);
                }
            }
        }
    }
}

// Handle overlap events
void UAttackComponent::OnHitboxOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult & SweepResult)
{
    AActor* OwnerActor = GetOwner();
    AGameCharacter* OwnerCharacter = nullptr;
    AController* OwnerInstigator = nullptr;
    float Damage = 0.0f;
    auto DamageTypeClass = UDamageType::StaticClass();
    UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());
    if (OwnerActor)
    {
        OwnerCharacter = Cast<AGameCharacter>(OwnerActor);
        OwnerInstigator = OwnerActor->GetInstigatorController();
    }

    if (OwnerCharacter)
    {
        Damage = OwnerCharacter->GetStatusComponent()->GetAttackPower();
    }

    if (OtherActor && OtherActor != GetOwner())
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());
        // Implement damage, effects, etc.
        UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, OwnerActor, DamageTypeClass);
        // if(HitParticles)
        // {
        //     UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
        // }
        // if (HitSound)
        // {
        //     UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        // }
    }
}