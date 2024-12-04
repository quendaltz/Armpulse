#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircleDecal.generated.h"

class UTimelineComponent;
UCLASS()
class ARMPULSE_API ACircleDecal : public AActor
{
    GENERATED_BODY()

public:
    ACircleDecal();

    UFUNCTION(BlueprintCallable, Category = "Indicator Functions")
    void SpawnArea();
    UFUNCTION(BlueprintCallable, Category = "Indicator Functions")
    void CreateArea(FVector Location, float Radius, float DesireDuration);

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Indicator Functions")
    void SpawnCircleDecal();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Indicator Props", meta = (AllowPrivateAccess = "true"));
    USceneComponent* DefaultSceneRoot;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Indicator Props", meta = (AllowPrivateAccess = "true"));
    UDecalComponent* Circumference;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Indicator Props", meta = (AllowPrivateAccess = "true"));
    UDecalComponent* Area;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Indicator Props", meta = (AllowPrivateAccess = "true"));
    float Duration;
};