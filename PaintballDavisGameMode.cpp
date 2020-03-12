// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PaintballDavisGameMode.h"
#include "PaintballDavisHUD.h"
#include "PaintballDavisCharacter.h"
#include "UObject/ConstructorHelpers.h"

APaintballDavisGameMode::APaintballDavisGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APaintballDavisHUD::StaticClass();
}
