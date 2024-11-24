// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

// Forward declaration
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ARMPULSE_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGamePlayerController();

	// Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	// Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	// Attack Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* AttackAction;

	// Cast Skill Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CastSkillAction;

	// Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> SkillBarWidgetClass;

protected:
	virtual void SetupInputComponent() override;
	void SetupWidget();

	virtual void BeginPlay();

	void OnMoveTriggered(const FInputActionValue& Value);
	void OnMoveReleased(const FInputActionValue& Value);

	void OnAttackTriggered();
	void OnSkillTriggered();

private:
	UUserWidget* SkillBarWidgetInstance;

};
