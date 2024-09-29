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

	// ####################################################################
    // Attack properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
    float Damage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
    float AttackRange;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
    bool IsAoE;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
    float AoERadius;

	class USphereComponent* HitboxComponent;

    // Function to trigger the attack
    UFUNCTION(BlueprintCallable, Category="Attack")
    void ExecuteAttack();

    // Function to apply damage (for AoE or single target)
    void ApplyDamage(AActor* Target);

    // Function to handle hit detection
    void PerformHitDetection();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void GetActorsInRadius(TArray<AActor*>& OutActors);
};
