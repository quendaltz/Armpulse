// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterCombatComponent::UCharacterCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	IsInAction = false;
}


// Called every frame
void UCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterCombatComponent::Attack()
{
	if (CanAction && !IsInAction)
	{
		OnAttack.Broadcast();

		IsInAction = true;
		CanAction = false;
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &UCharacterCombatComponent::ResetAnimation, AttackSpeed, false);
	}
}

void UCharacterCombatComponent::ApplyDamage(AActor* Target)
{

}

void UCharacterCombatComponent::ResetAnimation()
{
	IsInAction = false;
	CanAction = true;
}