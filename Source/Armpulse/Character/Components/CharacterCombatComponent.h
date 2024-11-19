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
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	UFUNCTION(BlueprintCallable, Category="Combat")
    void Attack(UCharacterStatusComponent* CharacterStatusComponent);
	void ResetAnimation(UCharacterStatusComponent* CharacterStatusComponent);

	UFUNCTION(BlueprintCallable, Category="Combat")
    void ApplyDamage(AActor* Target);

	UFUNCTION()
	float HandleTakeDamage(UCharacterStatusComponent* CharacterStatusComponent, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);


private:
	FTimerHandle ActionTimer;

	UPROPERTY(BlueprintAssignable, Category="Combat")
    FOnAttackDelegate OnAttack;
};
