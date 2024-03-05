// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeExtended.h"
#include "JsonObjectConverter.h"

void AGameModeExtended::BeginPlay()
{
	Super::BeginPlay();

	FJsonInitialPlayers ListPlayerData;

	FString JsonPath = "D:\\Repository\\Unreal Projects\\OnlineHUDExercise\\Content\\InitialData.json";
	FString FileData = "";

	UE_LOG(LogTemp, Warning, TEXT("Patch for json is %s"), *JsonPath);

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*JsonPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND FILE"));
		return;
	}

	FFileHelper::LoadFileToString(FileData, *JsonPath);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);


	if (FJsonObjectConverter::JsonObjectStringToUStruct(FileData, &ListPlayerData, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("CONVERTED"));
		UE_LOG(LogTemp, Warning, TEXT("First Name: %s Level: %d Alias: %s"), *ListPlayerData.InitialPlayersData[0].Name,
			ListPlayerData.InitialPlayersData[0].Level, *ListPlayerData.InitialPlayersData[0].Alias
			);
	}
}