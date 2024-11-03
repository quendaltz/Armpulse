// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARMPULSE_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetAttackRadius();
	void SetAttackRadius(float NewAttackRadius);

	float GetMoveSpeed();
	void SetMoveSpeed(float NewMoveSpeed);

	bool GetCanMove();
	void SetCanMove(bool NewCanMove);

private:
	// combat section ------------------------------------------------------------------------------------------
	float Attack;
	float AttackRadius;
	float Defense;
	float Health;
	float AttackSpeed;

	bool IsActing;
	bool CanAct;

	// movement section
	float MoveSpeed;
	float DashSpeed;

	bool CanDash;
	bool CanMove;
};
