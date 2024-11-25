// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameCharacter.h"
#include "PlayerGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class ARMPULSE_API APlayerGameCharacter : public AGameCharacter
{
	GENERATED_BODY()
	
public:
	APlayerGameCharacter();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
};
