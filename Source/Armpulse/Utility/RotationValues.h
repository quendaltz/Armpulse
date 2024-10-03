// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ARMPULSE_API RotationValues
{
public:
	RotationValues();
	~RotationValues();

	static FRotator GetTurnUpRotateValue(); // up arrow key (0x +y) -> 180 degree (0x -y 0z)
	static FRotator GetTurnLeftRotateValue(); // left arrow key (-x 0y) -> 90 degree (-x 0y 0z)
	static FRotator GetTurnDownRotateValue(); // down arrow key (0x -y) -> 0 degree (0x +y 0z)
	static FRotator GetTurnRightRotateValue(); // right arrow key (+x 0y) -> 270 degree (+x 0y 0z)
};
