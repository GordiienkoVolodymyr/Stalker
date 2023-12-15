// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stalker_GameMode.h"
#include "Stalker_Character.h"
#include "UObject/ConstructorHelpers.h"

AStalker_GameMode::AStalker_GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
