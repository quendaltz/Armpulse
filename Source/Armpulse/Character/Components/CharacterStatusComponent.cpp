#include "CharacterStatusComponent.h"

UCharacterStatusComponent::UCharacterStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// ATK POW
float UCharacterStatusComponent::GetAttackPower()
{
	return AttackPower;
}

void UCharacterStatusComponent::SetAttackPower(float NewAttackPower)
{
	if (NewAttackPower < 0.0f)
	{
		NewAttackPower = 0.0f;
	}
	AttackPower = NewAttackPower;
}

// ATK SPD
float UCharacterStatusComponent::GetAttackSpeed()
{
	return AttackSpeed;
}

void UCharacterStatusComponent::SetAttackSpeed(float NewAttackSpeed)
{
	if (NewAttackSpeed < 0.0f)
	{
		NewAttackSpeed = 0.0f;
	}
	AttackSpeed = NewAttackSpeed;
}

// ATK RAD
float UCharacterStatusComponent::GetAttackRadius()
{
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

// DEF
float UCharacterStatusComponent::GetDefense()
{
	return Defense;
}

void UCharacterStatusComponent::SetDefense(float NewDefense)
{
	if (NewDefense < 0.0f)
	{
		NewDefense = 0.0f;
	}
	Defense = NewDefense;
}

// Max HP
float UCharacterStatusComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UCharacterStatusComponent::SetMaxHealth(float NewHealth)
{
	if (NewHealth < 1.0f)
	{
		NewHealth = 1.0f;
	}
	MaxHealth = NewHealth;
}

// HP
float UCharacterStatusComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UCharacterStatusComponent::SetCurrentHealth(float NewHealth)
{
	if (NewHealth < 0.0f)
	{
		NewHealth = 0.0f;
	}
	CurrentHealth = NewHealth;
}

// IS ACT
bool UCharacterStatusComponent::GetIsActing()
{
	return IsActing;
}

void UCharacterStatusComponent::SetIsActing(bool NewIsActing)
{
	IsActing = NewIsActing;
}

// ACT COND
bool UCharacterStatusComponent::GetCanAct()
{
	return CanAct;
}

void UCharacterStatusComponent::SetCanAct(bool NewCanAct)
{
	CanAct = NewCanAct;
}

// MOV SPD
float UCharacterStatusComponent::GetMoveSpeed()
{
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

// MOV COND
bool UCharacterStatusComponent::GetCanMove()
{
	return CanMove;
}

void UCharacterStatusComponent::SetCanMove(bool NewCanMove)
{
	CanMove = NewCanMove;
}

void UCharacterStatusComponent::ResetActionState()
{
	IsActing = false;
	CanAct = true;
}