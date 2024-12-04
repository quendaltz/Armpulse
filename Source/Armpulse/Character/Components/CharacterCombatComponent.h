// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Attack/AttackComponent.h"
#include "CharacterCombatComponent.generated.h"

class UAttackComponent;
class UCharacterStatusComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARMPULSE_API UCharacterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterCombatComponent();

	void Attack(UCharacterStatusComponent* CharacterStatusComponent, FVector HitboxSpawnLocation);
	void ResetAnimation(UCharacterStatusComponent* CharacterStatusComponent);
	float HandleTakeDamage(UCharacterStatusComponent* CharacterStatusComponent, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAttackComponent* AttackComponent;
};
