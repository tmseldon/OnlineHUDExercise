// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineHUDExerciseGameMode.h"
#include "OnlineHUDExerciseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOnlineHUDExerciseGameMode::AOnlineHUDExerciseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
