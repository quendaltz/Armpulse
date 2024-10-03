// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationValues.h"

RotationValues::RotationValues()
{
}

RotationValues::~RotationValues()
{
}

FRotator RotationValues::GetTurnDownRotateValue()
{
    return FRotator(0.0f, 0.0f, 0.0f);
}

FRotator RotationValues::GetTurnLeftRotateValue()
{
    return FRotator(0.0f, 90.0f, 0.0f);
}

FRotator RotationValues::GetTurnUpRotateValue()
{
    return FRotator(0.0f, 180.0f, 0.0f);
}

FRotator RotationValues::GetTurnRightRotateValue()
{
    return FRotator(0.0f, 270.0f, 0.0f);
}

