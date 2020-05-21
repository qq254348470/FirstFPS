// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstFPSGameMode.h"
#include "FirstFPSHUD.h"
#include "FirstFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstFPSGameMode::AFirstFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstFPSHUD::StaticClass();
}
