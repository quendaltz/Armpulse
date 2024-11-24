// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "CharacterStatusComponent.h"
#include "../Attack/AttackComponent.h"

// Sets default values for this component's properties
UCharacterCombatComponent::UCharacterCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
}


// Called when the game starts
void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
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
	OnAttack.Broadcast();
	FTimerDelegate TimerFunction;
	TimerFunction.BindLambda([this, CharacterStatusComponent]()
	{
		ResetAnimation(CharacterStatusComponent);
	});

	CharacterStatusComponent->SetIsActing(true);
	CharacterStatusComponent->SetCanAct(false);
	if (AttackComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("AttackComponent Detected"));
		AttackComponent->ExecuteAttack(100.0f/AttackSpeed);
	}

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, TimerFunction, 100.0f/AttackSpeed, false);
}

void UCharacterCombatComponent::ApplyDamage(AActor* Target)
{

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