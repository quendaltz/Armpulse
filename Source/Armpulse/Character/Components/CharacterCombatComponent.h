// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Attack/AttackComponent.h"
#include "CharacterCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackDelegate);

class UCharacterStatusComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARMPULSE_API UCharacterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCombatComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAttackComponent* AttackComponent;

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

	UFUNCTION()
	void HandleTakeDamage(UCharacterStatusComponent* CharacterStatusComponent, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	void ResetAnimation();

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	float AttackSpeed = 50.0f;
	FTimerHandle ActionTimer;

	bool CanAction;
	bool IsAction;
	bool IsAttack;

	UPROPERTY(BlueprintAssignable, Category="Combat")
    FOnAttackDelegate OnAttack;
};
