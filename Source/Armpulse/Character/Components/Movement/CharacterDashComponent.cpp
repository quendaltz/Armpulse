#include "CharacterDashComponent.h"

#include "Components/CapsuleComponent.h"

#include "../../Character/GameCharacter.h"

#include "Kismet/KismetSystemLibrary.h"

UCharacterDashComponent::UCharacterDashComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsDashing = false;
    DashProgress = 0.0f;
}

void UCharacterDashComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCharacterDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsDashing)
    {
        PerformDash(DeltaTime);
    }
}

void UCharacterDashComponent::StartDash(float Distance, float Speed = 1000.0f)
{
    if (bIsDashing) return;  // Prevent overlapping dashes

    AGameCharacter* OwnerCharacter = Cast<AGameCharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // set
    DashDistance = Distance;
    DashSpeed = Speed;
    float ActorCapsuleRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();

    DashStartLocation = OwnerCharacter->GetActorLocation();
    DashEndLocation = OwnerCharacter->GetForwardCharacterLocation(DashDistance);

    // Perform collision check to stop dash early if needed
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(OwnerCharacter);  // Ignore self

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        DashStartLocation,
        DashEndLocation,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeSphere(ActorCapsuleRadius),  // Adjust size to suit dash
        CollisionParams
    );

    if (bHit)
    {
        DashEndLocation = HitResult.Location;  // Stop at collision
    }

    // Start dashing
    bIsDashing = true;
    DashProgress = 0.0f;
}

void UCharacterDashComponent::PerformDash(float DeltaTime)
{
    if (!bIsDashing) return;

    AGameCharacter* OwnerCharacter = Cast<AGameCharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Interpolate between start and end locations
    DashProgress += DashSpeed * DeltaTime / DashDistance;
    DashProgress = FMath::Clamp(DashProgress, 0.0f, 1.0f);

    FVector NewLocation = FMath::Lerp(DashStartLocation, DashEndLocation, DashProgress);
    OwnerCharacter->SetActorLocation(NewLocation);

    if (DashProgress >= 1.0f)
    {
        StopDash();
    }
}

void UCharacterDashComponent::StopDash()
{
    bIsDashing = false;

    UE_LOG(LogTemp, Log, TEXT("Dash Complete!"));
}