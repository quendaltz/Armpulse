// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArmpulseGameMode.h"
#include "ArmpulsePlayerController.h"
#include "ArmpulseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArmpulseGameMode::AArmpulseGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AArmpulsePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}