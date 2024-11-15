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
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	

	float GetAttackPower();
	void SetAttackPower(float NewAttackPower);

	float GetAttackSpeed();
	void SetAttackSpeed(float NewAttackSpeed);

	float GetAttackRadius();
	void SetAttackRadius(float NewAttackRadius);

	float GetDefense();
	void SetDefense(float NewDefense);

	float GetHealth();
	void SetHealth(float NewHealth);

	float GetMoveSpeed();
	void SetMoveSpeed(float NewMoveSpeed);

	bool GetCanMove();
	void SetCanMove(bool NewCanMove);

private:
	// combat section ------------------------------------------------------------------------------------------
	float AttackPower;
	float AttackRadius;
	float AttackSpeed;
	float Defense;
	float Health;

	bool IsActing;
	bool CanAct;

	// movement section
	float MoveSpeed;
	float DashSpeed;

	bool CanDash;
	bool CanMove;
};
