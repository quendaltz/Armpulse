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
    UFUNCTION(BlueprintCallable, Category="Attack")
    void ExecuteAttack(float AttackDuration);

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimSequence* AttackAnimation;

    // Collision function for when the hitbox overlaps with another actor
    UFUNCTION()
    void OnHitboxOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
        bool bFromSweep, const FHitResult & SweepResult);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

};
