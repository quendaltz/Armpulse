// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Character/GameCharacter.h"
#include "../../Utility/Widgets/SkillSlot/SkillBar.h"

AGamePlayerController::AGamePlayerController()
{
	bShowMouseCursor = true;
}

void AGamePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (SkillBarWidgetClass) // Make sure to set this in the editor or via code
    {
        UUserWidget* SkillBarWidget = CreateWidget<UUserWidget>(this, SkillBarWidgetClass);
        if (SkillBarWidget)
        {
            SkillBarWidget->AddToViewport();
			FVector2D SkillBarWidgetPosition(100.0f, 50.0f);
			SkillBarWidget->SetPositionInViewport(SkillBarWidgetPosition, false);
        }
    }
}

void AGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup keyboard move input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnMoveTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AGamePlayerController::OnMoveReleased);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AGamePlayerController::OnMoveReleased);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AArmpulsePlayerController::OnSetDestinationReleased);

		// Setup keyboard combat input events
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGamePlayerController::OnAttackTriggered);
		EnhancedInputComponent->BindAction(CastSkillAction, ETriggerEvent::Started, this, &AGamePlayerController::OnSkillTriggered);

		// Setup touch input events
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AArmpulsePlayerController::OnInputStarted);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AArmpulsePlayerController::OnTouchTriggered);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AArmpulsePlayerController::OnTouchReleased);
		// EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AArmpulsePlayerController::OnTouchReleased);
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGamePlayerController::OnMoveTriggered(const FInputActionValue& Value)
{
	AGameCharacter* PlayerGameCharacter = Cast<AGameCharacter>(GetPawn());
	if (PlayerGameCharacter)
	{
		PlayerGameCharacter->MoveTriggered(Value);
	}
}

void AGamePlayerController::OnMoveReleased(const FInputActionValue& Value)
{
	AGameCharacter* PlayerGameCharacter = Cast<AGameCharacter>(GetPawn());
	if (PlayerGameCharacter)
	{
		PlayerGameCharacter->MoveCompleted(Value);
	}
}

void AGamePlayerController::OnAttackTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Attack"));
	AGameCharacter* PlayerGameCharacter = Cast<AGameCharacter>(GetPawn());
	if (PlayerGameCharacter)
	{
		PlayerGameCharacter->AttackTriggered();
	}
}

void AGamePlayerController::OnSkillTriggered()
{
	AGameCharacter* PlayerGameCharacter = Cast<AGameCharacter>(GetPawn());
	if (PlayerGameCharacter)
	{
		PlayerGameCharacter->CastSkill("Sword Rush");
	}
}