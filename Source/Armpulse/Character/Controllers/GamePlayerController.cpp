// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Character/GameCharacter.h"
#include "../Components/CharacterSkillComponent.h"
#include "../../Utility/Widgets/SkillSlot/SkillBar.h"

AGamePlayerController::AGamePlayerController()
{
	bShowMouseCursor = true;
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupWidget();
}

void AGamePlayerController::SetupInputComponent()
{
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

		// Setup keyboard combat input events
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGamePlayerController::OnAttackTriggered);
		EnhancedInputComponent->BindAction(CastSkillAction, ETriggerEvent::Started, this, &AGamePlayerController::OnSkillTriggered);
	}
}

void AGamePlayerController::SetupWidget()
{
	if (SkillBarWidgetClass) // Make sure to set this in the editor or via code
    {
        SkillBarWidgetInstance = CreateWidget<UUserWidget>(this, SkillBarWidgetClass);
        if (SkillBarWidgetInstance)
        {
            SkillBarWidgetInstance->AddToViewport();
			FVector2D SkillBarWidgetPosition(150.0f, 100.0f);
			SkillBarWidgetInstance->SetPositionInViewport(SkillBarWidgetPosition, false);

			USkillBar* SkillBar = Cast<USkillBar>(SkillBarWidgetInstance);
			if (SkillBar)
            {
				AGameCharacter* PlayerGameCharacter = Cast<AGameCharacter>(GetPawn());
				if (PlayerGameCharacter)
				{

					TArray<TSubclassOf<UCharacterSkillBase>> ActiveSkills = PlayerGameCharacter->GetSkillComponent()->GetActiveSkills();
					SkillBar->InitializeSkillBar(ActiveSkills);
				}
            }
        }
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
		bool CastSuccess = PlayerGameCharacter->CastSkill(0);
		if (CastSuccess && SkillBarWidgetInstance)
		{
			USkillBar* SkillBar = Cast<USkillBar>(SkillBarWidgetInstance);
			if (SkillBar)
			{
				SkillBar->StartCooldownTimer(0);
			}
		}
	}
}