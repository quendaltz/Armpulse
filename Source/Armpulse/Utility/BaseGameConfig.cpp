// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameConfig.h"

BaseGameConfig::BaseGameConfig()
{
}

BaseGameConfig::~BaseGameConfig()
{
}

FVector BaseGameConfig::BaseCharacterForwardDirection()
{
    // from blueprint >> front is left of player = -x
    return FVector(-1.0f, 0.0f, 0.0f);
}

FVector BaseGameConfig::BaseCharacterRightDirection()
{
    // from blueprint >> right is toward player = -y
    return FVector(0.0f, -1.0f, 0.0f);
}