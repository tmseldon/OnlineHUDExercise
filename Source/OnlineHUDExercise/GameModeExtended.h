// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeExtended.generated.h"

/*
This struct encapsulates the data of each player
*/
USTRUCT()
struct FJsonDataPlayer
{
	GENERATED_BODY();

public:

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Alias;

	UPROPERTY()
	int Level;

	UPROPERTY()
	int Pic;

	UPROPERTY()
	uint32 LastSeen;

	UPROPERTY()
	bool Online;
};

/*
This struct encapsulates all the potential players on this example
*/
USTRUCT()
struct FJsonInitialPlayers
{
	GENERATED_BODY();

public:

	UPROPERTY()
	TArray<FJsonDataPlayer> InitialPlayersData;
};


/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API AGameModeExtended : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
