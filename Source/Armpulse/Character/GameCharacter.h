// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCharacter.generated.h"

class UCapsuleComponent;
UCLASS()
class ARMPULSE_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	AGameCharacter();

	// ####################################################################
	// character box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* CharacterMesh;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// class UPaperFlipbookComponent* CharacterFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* IdleFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* RunFlipbook;

	// ####################################################################
	// movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 100.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MoveDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	// ####################################################################
	// components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    class UCharacterCombatComponent* CombatComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	void MoveTriggered(const struct FInputActionValue& Value);
	void MoveCompleted(const struct FInputActionValue& Value);
	void AttackTriggered();
};
