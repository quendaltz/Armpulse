#include "AttackIndicator.h"

#include "Components/DecalComponent.h"

#include "CircleDecal.h"
#include "UObject/ConstructorHelpers.h"

AAttackIndicator::AAttackIndicator()
{
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<ACircleDecal> CircleDecalBPClass(TEXT("/Game/Blueprints/Character/Particles/BP_CircleArea"));
    if (CircleDecalBPClass.Succeeded())
    {
        CircleDecalClass = CircleDecalBPClass.Class;
    }
}

void AAttackIndicator::BeginPlay()
{
	Super::BeginPlay();

    if (CircleDecalClass)
    {
        // Spawn the CircleDecal actor
        // CircleDecalInstance = GetWorld()->SpawnActor<ACircleDecal>(CircleDecalClass, GetActorLocation(), GetActorRotation());
        // if (CircleDecalInstance)
        // {
        //     // Call a function on the CircleDecal instance
        //     CircleDecalInstance->BlueprintFunction();
        // }
    }
}

void AAttackIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackIndicator::SpawnCircleArea(FVector Location, float Radius, float Duration)
{
    // Set the decal properties
    // CircleDecalArea->SetWorldLocation(Location);
    // CircleDecalArea->SetWorldRotation(Rotation);
    // CircleDecalArea->DecalSize = FVector(Radius, Radius, 10.0f);
    // ACircleDecal* CircleDecalArea = Cast<ACircleDecal>(CircleDecalAreaClass);
    if (CircleDecalClass)
    {
        UE_LOG(LogTemp, Display, TEXT("CircleDecalClass found"));
        // Spawn the CircleDecal actor
        ACircleDecal* CircleDecalInstance = GetWorld()->SpawnActor<ACircleDecal>(CircleDecalClass, Location, GetActorRotation());
        if (CircleDecalInstance)
        {
            UE_LOG(LogTemp, Display, TEXT("CircleDecalInstance found"));
            // Call a function on the CircleDecal instance
            CircleDecalInstance->CreateArea(Location, Radius, Duration);
            CircleDecalInstance->SpawnArea();
        }

        //CircleDecalClass->CreateArea(Location, Radius, Duration);
        //CircleDecalClass->SpawnArea();
        // TSubclassOf<AActor> CircleDecalAreaActor = ACircleDecal::StaticClass()->CreateArea(Radius, Duration);
        // CircleDecalAreaClass
        // Spawn the actor from the blueprint
        // CircleDecalArea = GetWorld()->SpawnActor<AActor>(CircleDecalAreaActor, Location, GetActorRotation());
    }
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