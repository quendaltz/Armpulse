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

// HP	
float UCharacterStatusComponent::GetHealth()
{
	return Health;
}

void UCharacterStatusComponent::SetHealth(float NewHealth)
{
	if (NewHealth < 0.0f)
	{
		NewHealth = 0.0f;
	}
	Health = NewHealth;
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