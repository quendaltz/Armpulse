#include "AttackIndicator.h"

#include "Components/DecalComponent.h"

AAttackIndicator::AAttackIndicator()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackDecalArea = CreateDefaultSubobject<UDecalComponent>(TEXT("AttackDecalArea"));
    RootComponent = AttackDecalArea;

    AttackDecalArea->DecalSize = FVector(200.0f, 500.0f, 10.0f);
    AttackDecalArea->SetVisibility(true);
}

void AAttackIndicator::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackIndicator::PrepareAttack(FVector Location, FRotator Rotation, float PrepareTime)
{
    // Set the decal properties
    AttackDecalArea->SetWorldLocation(Location);
    AttackDecalArea->SetWorldRotation(Rotation);

    // Hide the decal after a delay (e.g., before the attack lands)
    UE_LOG(LogTemp, Display, TEXT("SHOWSHOWHO"));
    FTimerHandle DecalTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        DecalTimerHandle, 
        this, 
        &AAttackIndicator::HideAttackIndicator, 
        PrepareTime,  // Duration to display the decal
        false
    );
}

void AAttackIndicator::HideAttackIndicator()
{
    AttackDecalArea->SetVisibility(false);
}

void AAttackIndicator::SetIndicatorArea(FVector NewArea)
{
    AttackDecalArea->DecalSize = NewArea;
}