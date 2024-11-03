// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatusComponent.h"

// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UCharacterStatusComponent::GetAttackRadius() {
	return AttackRadius;
}

void UCharacterStatusComponent::SetAttackRadius(float NewAttackRadius)
{
	if (NewAttackRadius < 0.0f)
	{
		NewAttackRadius = 0.0f;
	}
	AttackRadius = NewAttackRadius;
}

float UCharacterStatusComponent::GetMoveSpeed() {
	return MoveSpeed;
}

void UCharacterStatusComponent::SetMoveSpeed(float NewMoveSpeed)
{
	if (NewMoveSpeed < 0.0f)
	{
		NewMoveSpeed = 0.0f;
	}
	MoveSpeed = NewMoveSpeed;
}

bool UCharacterStatusComponent::GetCanMove()
{
	return CanMove;
}

void UCharacterStatusComponent::SetCanMove(bool NewCanMove)
{
	CanMove = NewCanMove;
}