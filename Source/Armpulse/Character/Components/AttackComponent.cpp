// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
    Damage = 10.0f;
    AttackRange = 100.0f;
    IsAoE = false;  // Default is single target attack
    AoERadius = 300.0f;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HitboxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitboxComponent"));
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        USceneComponent* RootComponent = OwnerActor->GetRootComponent();

        if (RootComponent)
        {
            HitboxComponent->SetupAttachment(RootComponent);  // Attach to the root component
        }
    }
    HitboxComponent->SetSphereRadius(AttackRange);
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
    if (IsAoE)
    {
        PerformHitDetection();  // AoE attack
    }
    else
    {
        PerformHitDetection();  // Single target attack (use hitbox)
    }
}

void UAttackComponent::PerformHitDetection()
{
    if (IsAoE)
    {
        TArray<AActor*> HitActors;
        GetActorsInRadius(HitActors);

        for (AActor* Actor : HitActors)
        {
            ApplyDamage(Actor);
        }
    }
    else
    {
        // Handle hitbox collision (single target)
        AActor* Owner = GetOwner();
        if (!Owner) return;

        // Check overlap of hitbox with other actors
        TArray<AActor*> OverlappingActors;
        HitboxComponent->GetOverlappingActors(OverlappingActors);

        for (AActor* Actor : OverlappingActors)
        {
            if (Actor != Owner)  // Ignore self
            {
                ApplyDamage(Actor);
            }
        }
    }
}

void UAttackComponent::ApplyDamage(AActor* Target)
{
    if (Target)
    {
        // Apply damage to the target
        UGameplayStatics::ApplyDamage(Target, Damage, nullptr, GetOwner(), nullptr);
        UE_LOG(LogTemp, Log, TEXT("Applied %f damage to %s"), Damage, *Target->GetName());
    }
}

void UAttackComponent::GetActorsInRadius(TArray<AActor*>& OutActors)
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // Use Unreal's built-in functionality to get actors within the AoE radius
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), OutActors);

    // Filter by distance to ensure they're within AoE radius
    for (int32 i = OutActors.Num() - 1; i >= 0; i--)
    {
        AActor* Actor = OutActors[i];
        if (Actor && FVector::Dist(Owner->GetActorLocation(), Actor->GetActorLocation()) > AoERadius)
        {
            OutActors.RemoveAt(i);
        }
    }
}