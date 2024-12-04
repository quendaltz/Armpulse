#include "CircleDecal.h"

#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TimelineComponent.h"

ACircleDecal::ACircleDecal()
{
    PrimaryActorTick.bCanEverTick = true;

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;

    Circumference = CreateDefaultSubobject<UDecalComponent>(TEXT("Circumference"));
    Circumference->SetupAttachment(DefaultSceneRoot);
    Circumference->SetRelativeRotation(FRotator(270.0f, 180.0f, 180.0f));
    
    Area = CreateDefaultSubobject<UDecalComponent>(TEXT("Area"));
    Area->SetupAttachment(DefaultSceneRoot);
    Area->SetRelativeRotation(FRotator(270.0f, 180.0f, 180.0f));

    Duration = 1.0f;
}

void ACircleDecal::CreateArea(FVector Location, float Radius, float DesireDuration)
{
    UE_LOG(LogTemp, Display, TEXT("Create area %f") , Radius);
    Circumference->DecalSize = FVector(1.0f, Radius, Radius);
    Area->DecalSize = FVector(1.0f, Radius, Radius);
    Duration = DesireDuration;

    // SetActorLocation(Location);
}

void ACircleDecal::SpawnArea()
{
    SpawnCircleDecal();
}