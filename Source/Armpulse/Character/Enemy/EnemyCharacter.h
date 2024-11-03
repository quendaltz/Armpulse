// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARMPULSE_API AEnemyCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* CharacterMesh;
	
};
