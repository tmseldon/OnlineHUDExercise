// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonDataPlayer.generated.h"

/*
This struct encapsulates the data of each player
*/
USTRUCT(BlueprintType)
struct FJsonDataPlayer
{
	GENERATED_BODY();

public:

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString Alias;

	UPROPERTY(BlueprintReadOnly)
	int Level;

	UPROPERTY(BlueprintReadOnly)
	int Pic;

	UPROPERTY(BlueprintReadOnly)
	int LastSeen;

	UPROPERTY(BlueprintReadOnly)
	bool Online;
};

/*
This struct encapsulates all the potential players on this example
*/
USTRUCT(BlueprintType)
struct FJsonInitialPlayers
{
	GENERATED_BODY();

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<FJsonDataPlayer> InitialPlayersData;
};

