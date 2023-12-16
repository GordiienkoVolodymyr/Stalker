// Copyright Epic Games, Inc. All Rights Reserved.

#include "Stalker_Game_Mode.h"
#include "Stalker_Character.h"
#include "UObject/ConstructorHelpers.h"

AStalker_Game_Mode::AStalker_Game_Mode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
