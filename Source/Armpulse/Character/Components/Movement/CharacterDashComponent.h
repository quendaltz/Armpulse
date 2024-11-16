#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDashComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARMPULSE_API UCharacterDashComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterDashComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    FVector DashStartLocation;
    FVector DashEndLocation;
    float DashProgress;
    bool bIsDashing;

    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashDistance = 0.0f;  // Distance to dash

    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashSpeed = 1000.0f;  // Speed in units per second

    FTimerHandle DashTimerHandle;

    void PerformDash(float DeltaTime);
    void StopDash();

public:
    void StartDash(float Distance, float Speed);
};