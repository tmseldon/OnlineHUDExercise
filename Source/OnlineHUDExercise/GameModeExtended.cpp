// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeExtended.h"
#include "OnlineHUDExerciseCharacter.h"
#include "UObject/ConstructorHelpers.h"

//Copying this constructor from the generated code for the Third Person View Template from Unreal
AGameModeExtended::AGameModeExtended()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGameModeExtended::BeginPlay()
{
	Super::BeginPlay();
}