// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeExtended.generated.h"

UCLASS()
class ONLINEHUDEXERCISE_API UEncapsulateData : public UObject
{
	GENERATED_BODY()

public:

	FString Nombre;
	FString Alias;
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

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "FJsonInitialPlayers"))
	FInstancedStruct DataCardInitial;

public:

	AGameModeExtended();
	
};
