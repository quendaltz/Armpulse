// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameCharacter.h"
#include "PlayerGameCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARMPULSE_API APlayerGameCharacter : public AGameCharacter
{
	GENERATED_BODY()
	
public:
	APlayerGameCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* CharacterMesh;

protected:
	virtual void BeginPlay() override;

private:
};
