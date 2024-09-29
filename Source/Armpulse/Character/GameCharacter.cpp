// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
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
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGameCharacter::MoveTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Move"));
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (CanMove)
	{
		MoveDirection = MoveActionValue;

		if (MoveDirection.Length() > 0.0f)
		{
			if (MoveDirection.Length() > 1.0f)
			{
				MoveDirection.Normalize();
			}
			float DeltaTime = GetWorld()->DeltaTimeSeconds;
			FVector2D DistanceToMove = MoveDirection * MoveSpeed * DeltaTime;

			FVector CurrentLocation = GetActorLocation();

			FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, 0.0f);
			if (false)
			{
				NewLocation -= FVector(DistanceToMove.X, 0.0f, 0.0f);
			}
			
			NewLocation += FVector(0.0f, -DistanceToMove.Y, 0.0f);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, NewLocation.ToString(), IsInMapBoundsVertical(NewLocation.Y));
			if (false)
			{
				NewLocation -= FVector(0.0f, -DistanceToMove.Y, 0.0f);
			}
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, NewLocation.ToString());
			SetActorLocation(NewLocation);
		}
	}
}

void AGameCharacter::MoveCompleted(const FInputActionValue& Value)
{
	MoveDirection = FVector2D(0.0f, 0.0f);
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