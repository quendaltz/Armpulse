// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Components/CharacterCombatComponent.h"
#include "../Components/CharacterStatusComponent.h"
#include "../Components/Movement/CharacterDashComponent.h"
#include "../../Utility/BaseGameConfig.h"

#include "DrawDebugHelpers.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	// CharacterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CharacterFlipbook"));
	// CharacterFlipbook->SetupAttachment(RootComponent);

	// Setup gameplay components
	CombatComponent = CreateDefaultSubobject<UCharacterCombatComponent>(TEXT("CombatComponent"));
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("StatusComponent"));
	DashComponent = CreateDefaultSubobject<UCharacterDashComponent>(TEXT("DashComponent"));

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CapsuleComponent)
    {
        FVector CapsuleLocation = CapsuleComponent->GetComponentLocation();
        float CapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
        float CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
        
        FColor DebugColor = FColor::Red;
        float Duration = 0.0f; // The sphere will stay for 5 seconds
        float Thickness = 2.0f; // Optional, for the line thickness

        DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, DebugColor, false, Duration, 0, Thickness);
    }

	if (StatusComponent)
	{
		auto Test = StatusComponent->GetHealth();
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s, %f"), *this->GetName(), Test);
	}
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FVector AGameCharacter::GetForwardCharacterLocation(float ForwardDistance)
{
	FVector CurrentLocation = GetActorLocation();
	FVector RightVector = GetActorRightVector();
	return CurrentLocation + (RightVector * ForwardDistance);
}

void AGameCharacter::ExecuteMontage(UAnimMontage* MontageToPlay)
{
	if (CharacterMesh)
	{
		UE_LOG(LogTemp, Log, TEXT("CharacterMesh"));
		UAnimInstance* Testt = CharacterMesh->GetAnimInstance();
		if (Testt)
		{
			UE_LOG(LogTemp, Log, TEXT("Montage_Play"));
			CharacterMesh->GetAnimInstance()->Montage_Stop(0.0f);
			CharacterMesh->GetAnimInstance()->Montage_Play(MontageToPlay, 1.0f);
		}
	}
}

void AGameCharacter::ExecuteAnimation(UAnimSequence* AnimationToPlay)
{
	if (CharacterMesh)
	{
		UE_LOG(LogTemp, Log, TEXT("CharacterMesh"));
		UE_LOG(LogTemp, Log, TEXT("PlayAnimation"));
		CharacterMesh->PlayAnimation(AnimationToPlay, false);
	}
}

void AGameCharacter::MoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (StatusComponent->GetCanMove() && !MoveActionValue.IsNearlyZero())
	{
		MoveActionValue.Normalize();
		float DeltaTime = GetWorld()->DeltaTimeSeconds;

		FVector2D MoveDistance = MoveActionValue * StatusComponent->GetMoveSpeed() * DeltaTime;
		FVector CurrentLocation = GetActorLocation();

		// set initial desired location
		FVector NewLocation = CurrentLocation + FVector(MoveDistance.X, -MoveDistance.Y, 0.0f);
		if (false) // blocked by left/right obstacle
		{
			// remove corresponding movement direction
			NewLocation -= FVector(MoveDistance.X, 0.0f, 0.0f);
		}
		if (false) // blocked by up/down obstacle
		{
			// remove corresponding movement direction
			NewLocation -= FVector(0.0f, -MoveDistance.Y, 0.0f);
		}

		SetActorLocation(NewLocation);

		// rotate character
		FVector MoveDirection = (BaseGameConfig::BaseCharacterForwardDirection() * MoveActionValue.Y) + (BaseGameConfig::BaseCharacterRightDirection() * MoveActionValue.X);
		MoveDirection.Normalize();
		FRotator NewRotation = MoveDirection.Rotation();
		SetActorRotation(NewRotation);
	}
}

void AGameCharacter::MoveCompleted(const FInputActionValue& Value)
{

}

// void AGameCharacter::MoveTriggered(const FInputActionValue& Value)
// {
// 	FVector2D MoveActionValue = Value.Get<FVector2D>();
// 	if (CanMove)
// 	{
// 		MoveDirection = MoveActionValue;
// 		CharacterFlipbook->SetFlipbook(RunFlipbook);
// 		FVector FlipbookScale = CharacterFlipbook->GetComponentScale();
// 		if (MoveDirection.X < 0.0f)
// 		{
// 			if (FlipbookScale.X < 0.0f)
// 			{
// 				CharacterFlipbook->SetWorldScale3D(FVector(1.0f, FlipbookScale.Y, FlipbookScale.Z));
// 			}
// 		}
// 		else if (MoveDirection.X > 0.0f)
// 		{
// 			if (FlipbookScale.X > 0.0f)
// 			{
// 				CharacterFlipbook->SetWorldScale3D(FVector(-1.0f, FlipbookScale.Y, FlipbookScale.Z));
// 			}
// 		}
// 	}
// }

// void AGameCharacter::MoveCompleted(const FInputActionValue& Value)
// {
// 	MoveDirection = FVector2D(0.0f, 0.0f);
// 	CharacterFlipbook->SetFlipbook(IdleFlipbook);
// }

void AGameCharacter::AttackTriggered()
{
	if (CombatComponent)
	{
		CombatComponent->Attack();
	}
}

float AGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CombatComponent)
    {
        CombatComponent->HandleTakeDamage(StatusComponent, DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    }
    
    return DamageAmount;
}