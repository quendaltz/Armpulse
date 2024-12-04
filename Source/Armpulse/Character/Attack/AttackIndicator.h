#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackIndicator.generated.h"

class ACircleDecal;
UCLASS()
class ARMPULSE_API AAttackIndicator : public AActor
{
	GENERATED_BODY()
	
public:
	AAttackIndicator();

	void PrepareAttack(FVector Location, FRotator Rotation, float PrepareTime);
    void HideAttackIndicator();
	void SetIndicatorArea(FVector NewArea);
	void SpawnCircleArea(FVector Location, float Radius, float Duration);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* AttackDecalArea;

	UPROPERTY(EditAnywhere, Category = "Indicator", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ACircleDecal> CircleDecalClass;

    // UPROPERTY(meta = (AllowPrivateAccess = "true"))
    // ACircleDecal* CircleDecalInstance;
};