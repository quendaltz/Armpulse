// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArmpulseGameMode.h"
#include "../Character/Controllers/GamePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AArmpulseGameMode::AArmpulseGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/BP_GameCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Input/BP_GamePlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}