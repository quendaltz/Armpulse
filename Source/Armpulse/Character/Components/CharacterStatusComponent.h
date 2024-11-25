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
	UCharacterStatusComponent();

	float GetAttackPower();
	void SetAttackPower(float NewAttackPower);

	float GetAttackSpeed();
	void SetAttackSpeed(float NewAttackSpeed);

	float GetAttackRadius();
	void SetAttackRadius(float NewAttackRadius);

	float GetDefense();
	void SetDefense(float NewDefense);

	float GetMaxHealth();
	void SetMaxHealth(float NewHealth);

	float GetCurrentHealth();
	void SetCurrentHealth(float NewHealth);

	bool GetIsActing();
	void SetIsActing(bool NewIsActing);

	bool GetCanAct();
	void SetCanAct(bool NewCanAct);

	float GetMoveSpeed();
	void SetMoveSpeed(float NewMoveSpeed);

	bool GetCanMove();
	void SetCanMove(bool NewCanMove);

	void ResetActionState();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// combat section ------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float AttackPower;
	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float AttackRadius;
	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float AttackSpeed;

	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float Defense;

	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	bool IsActing;
	bool CanAct;

	// movement section
	UPROPERTY(EditAnywhere, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;
	float DashSpeed;

	bool CanDash;
	bool CanMove;
};
