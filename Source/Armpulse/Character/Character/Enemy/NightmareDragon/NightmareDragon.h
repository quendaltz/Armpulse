#pragma once

#include "CoreMinimal.h"
#include "../EnemyCharacter.h"
#include "NightmareDragon.generated.h"

UCLASS()
class ARMPULSE_API ANightmareDragon : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ANightmareDragon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void PerformAction();
	void SweepAttack();

private:
	FTimerHandle AttackTimerHandle;
	
};
