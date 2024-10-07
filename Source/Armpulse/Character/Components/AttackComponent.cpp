// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "../GameCharacter.h"

#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    Damage = 10.0f;
    AttackRange = 100.0f;
    IsAoE = false;  // Default is single target attack
    AoERadius = 300.0f;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

    SphereHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("SphereHitbox"));
    BoxHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxHitbox"));
    CapsuleHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleHitbox"));

    bIsHitboxActive = false;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

    SphereHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CapsuleHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SphereHitbox->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnHitboxOverlap);
    BoxHitbox->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnHitboxOverlap);
    CapsuleHitbox->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnHitboxOverlap);
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (SphereHitbox->IsActive())
    {
        SphereHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        FVector SphereLocation = SphereHitbox->GetComponentLocation();
        float SphereRadius = SphereHitbox->GetScaledSphereRadius();
        DrawDebugSphere(GetWorld(), SphereLocation, SphereRadius, 12, FColor::Green, 0.0f, 2.0f);
    }
    else if (BoxHitbox->IsActive())
    {
        BoxHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        FVector BoxLocation = BoxHitbox->GetComponentLocation();
        FVector BoxExtent = BoxHitbox->GetScaledBoxExtent();
        DrawDebugBox(GetWorld(), BoxLocation, BoxExtent, FColor::Blue);
    }
    else if (CapsuleHitbox->IsActive())
    {
        CapsuleHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        FVector CapsuleLocation = CapsuleHitbox->GetComponentLocation();
        float CapsuleRadius;
        float CapsuleHalfHeight;
        CapsuleHitbox->GetScaledCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
        DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Red, false, 0.0f, 0, 2.0f);
    }
}

void UAttackComponent::ExecuteAttack()
{
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        float ActorCapsuleRadius = 0.0f;
        AGameCharacter* Character = Cast<AGameCharacter>(OwnerActor);
        if (Character)
        {
            ActorCapsuleRadius = Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
        }
        FVector ActorLocation = OwnerActor->GetActorLocation();
        FVector ForwardVector = OwnerActor->GetActorForwardVector();
        FVector RightVector = OwnerActor->GetActorRightVector();
        FVector HitboxSpawnLocation = ActorLocation + (ForwardVector * ActorCapsuleRadius);

		UE_LOG(LogTemp, Log, TEXT("Capsule Radius %s"), *OwnerActor->GetActorRotation().ToString());
		UE_LOG(LogTemp, Log, TEXT("ForwardVector %s"), *ForwardVector.ToString());
		UE_LOG(LogTemp, Log, TEXT("RightVector %s"), *RightVector.ToString());
        CreateHitbox(HitboxSpawnLocation, 100);
    }

    // if (IsAoE)
    // {
    //     PerformHitDetection();  // AoE attack
    // }
    // else
    // {
    //     PerformHitDetection();  // Single target attack (use hitbox)
    // }
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

// Function to create a dynamic hitbox (sphere, box, or capsule)
void UAttackComponent::CreateHitbox(FVector Location, float Radius, float Height, FVector BoxExtent)
{
    // Set the location of the hitboxes
    SphereHitbox->SetWorldLocation(Location);
    BoxHitbox->SetWorldLocation(Location);
    CapsuleHitbox->SetWorldLocation(Location);

    // Set default to sphere hitbox if box extent is not set
    if (BoxExtent == FVector(0.0f))
    {
        SetSphereHitbox(Radius);
    }
    else
    {
        SetBoxHitbox(BoxExtent);
    }

    // If height is set, assume capsule hitbox
    if (Height > 0.0f)
    {
        SetCapsuleHitbox(Radius, Height);
    }
}

// Enable the hitbox for collisions
void UAttackComponent::EnableHitbox()
{
    bIsHitboxActive = true;

    // Activate collision depending on the hitbox type
    if (SphereHitbox->IsActive())
    {
        SphereHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
    else if (BoxHitbox->IsActive())
    {
        BoxHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
    else if (CapsuleHitbox->IsActive())
    {
        CapsuleHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}

// Disable the hitbox for collisions
void UAttackComponent::DisableHitbox()
{
    bIsHitboxActive = false;

    SphereHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CapsuleHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Set the sphere hitbox size
void UAttackComponent::SetSphereHitbox(float Radius)
{
    SphereHitbox->SetSphereRadius(Radius);
    SphereHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereHitbox->SetActive(true);
}

// Set the box hitbox size
void UAttackComponent::SetBoxHitbox(FVector BoxExtent)
{
    BoxHitbox->SetBoxExtent(BoxExtent);
    BoxHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Set the capsule hitbox size
void UAttackComponent::SetCapsuleHitbox(float Radius, float HalfHeight)
{
    CapsuleHitbox->SetCapsuleRadius(Radius);
    CapsuleHitbox->SetCapsuleHalfHeight(HalfHeight);
    CapsuleHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Handle overlap events
void UAttackComponent::OnHitboxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());
        // Implement damage, effects, etc.
    }
}