// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ARMPULSE_API BaseGameConfig
{
public:
	BaseGameConfig();
	~BaseGameConfig();

	static FVector BaseCharacterForwardDirection();
	static FVector BaseCharacterRightDirection();
};
