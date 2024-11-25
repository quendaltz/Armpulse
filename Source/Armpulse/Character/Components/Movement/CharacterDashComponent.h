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

    void StartDash(float Distance, float Speed);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    FVector DashStartLocation;
    FVector DashEndLocation;
    float DashProgress;
    bool bIsDashing;

    FTimerHandle DashTimerHandle;
    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashDistance = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashSpeed = 1000.0f;

    void PerformDash(float DeltaTime);
    void StopDash();
    
};