// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameCharacter.h"
#include "EliteDummy.generated.h"

/**
 * 
 */
UCLASS()
class ARMPULSE_API AEliteDummy : public AGameCharacter
{
	GENERATED_BODY()

public:
	AEliteDummy();

protected:
	virtual void BeginPlay() override;

private:
};
