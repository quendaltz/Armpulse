// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "CharacterStatusComponent.h"
#include "../Attack/AttackComponent.h"

UCharacterCombatComponent::UCharacterCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
}

void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterCombatComponent::Attack(UCharacterStatusComponent* CharacterStatusComponent)
{	
	if (!CharacterStatusComponent) return;
	
	bool IsActing = CharacterStatusComponent->GetIsActing();
	bool CanAction = CharacterStatusComponent->GetCanAct();
	if (!CanAction && IsActing) return;

	float AttackSpeed = CharacterStatusComponent->GetAttackSpeed();
	FTimerHandle ResetAnimationTimer;
	FTimerDelegate ResetAnimationFunction;
	ResetAnimationFunction.BindLambda([this, CharacterStatusComponent]()
	{
		ResetAnimation(CharacterStatusComponent);
	});

	CharacterStatusComponent->SetIsActing(true);
	CharacterStatusComponent->SetCanAct(false);
	if (AttackComponent)
	{
		AttackComponent->ExecuteAttack(100.0f/AttackSpeed);
	}

	GetWorld()->GetTimerManager().SetTimer(ResetAnimationTimer, ResetAnimationFunction, 100.0f/AttackSpeed, false);
}

float UCharacterCombatComponent::HandleTakeDamage(UCharacterStatusComponent* CharacterStatusComponent, float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = 0.0f;
	if (DamageAmount <= 0.f)
	{
		return ActualDamage;
	}

	if (CharacterStatusComponent)
	{
		float CurrentHealth = CharacterStatusComponent->GetCurrentHealth();
		if (CurrentHealth > 0.f)
		{
			float CurrentDefense = CharacterStatusComponent->GetDefense();
			ActualDamage = DamageAmount - CurrentDefense;
			CurrentHealth = CurrentHealth - ActualDamage;
			CharacterStatusComponent->SetCurrentHealth(CurrentHealth);
		}
	}

	return ActualDamage;
}

void UCharacterCombatComponent::ResetAnimation(UCharacterStatusComponent* CharacterStatusComponent)
{
	CharacterStatusComponent->ResetActionState();
}