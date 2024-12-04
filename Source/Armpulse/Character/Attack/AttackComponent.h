// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARMPULSE_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

    // Function to trigger the attack
    void ExecuteAttack(FVector HitboxSpawnLocation, FCollisionShape AttackHitbox, FRotator AttackRotation, float AttackAnimationLockTime, float ProcessAttackAfterAnimationTime = 0.0f);

protected:
	virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimSequence* AttackAnimation;
private:

};
