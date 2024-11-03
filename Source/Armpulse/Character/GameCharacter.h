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

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// class UPaperFlipbookComponent* CharacterFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* IdleFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* RunFlipbook;

protected:
	virtual void BeginPlay() override;

private:
	// character box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;
	// components
    class UCharacterStatusComponent* StatusComponent;
    class UCharacterCombatComponent* CombatComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	FORCEINLINE UCharacterStatusComponent* GetStatusComponent() const { return StatusComponent; }
	FORCEINLINE UCharacterCombatComponent* GetCombatComponent() const { return CombatComponent; }

	void MoveTriggered(const struct FInputActionValue& Value);
	void MoveCompleted(const struct FInputActionValue& Value);
	void AttackTriggered();
};
