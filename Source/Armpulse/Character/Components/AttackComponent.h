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

    // Function to create a hitbox (sphere, box, or capsule)
    void CreateHitbox(FVector Location, float Radius, float Height = 0.0f, FVector BoxExtent = FVector(0.0f));

    // Function to enable or disable the hitbox
    void EnableHitbox();
    void DisableHitbox();

    // Functions to dynamically adjust hitbox size
    void SetSphereHitbox(float Radius);
    void SetBoxHitbox(FVector BoxExtent);
    void SetCapsuleHitbox(float Radius, float HalfHeight);

protected:
	virtual void BeginPlay() override;

    UPROPERTY()
    class USphereComponent* SphereHitbox;

    UPROPERTY()
    class UBoxComponent* BoxHitbox;

    UPROPERTY()
    class UCapsuleComponent* CapsuleHitbox;

    // General flag to track the hitbox's active state
    bool bIsHitboxActive;

    // Collision function for when the hitbox overlaps with another actor
    UFUNCTION()
    void OnHitboxOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
        bool bFromSweep, const FHitResult & SweepResult);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void GetActorsInRadius(TArray<AActor*>& OutActors);
};
