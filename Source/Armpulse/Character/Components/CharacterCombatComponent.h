// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARMPULSE_API UCharacterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Combat")
    void Attack();

	UFUNCTION(BlueprintCallable, Category="Combat")
    void ApplyDamage(AActor* Target);

	void ResetAnimation();

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackSpeed;
	FTimerHandle ActionTimer;

	bool CanAction;
	bool IsInAction;

	UPROPERTY(BlueprintAssignable, Category="Combat")
    FOnAttackDelegate OnAttack;
};