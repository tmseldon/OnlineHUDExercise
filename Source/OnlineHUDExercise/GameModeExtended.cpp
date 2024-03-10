// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeExtended.h"
#include "JsonDataPlayer.h"
#include "JsonObjectConverter.h"
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

	for (FJsonDataPlayer playerInitialData : ListPlayerData.InitialPlayersData)
	{
		UEncapsulateData* currentCapsule = NewObject<UEncapsulateData>();
		currentCapsule->Nombre = playerInitialData.Name;
		currentCapsule->Alias = playerInitialData.Alias;

		DataTestEncapsulated.Add(currentCapsule);
	}

	for (UEncapsulateData* testidCapsule : DataTestEncapsulated)
	{
		FString TextoPrueba = testidCapsule->Nombre;
		UE_LOG(LogTemp, Warning, TEXT("Primer nombre objeto: %s alias %s"), *TextoPrueba, *testidCapsule->Alias);
	}
}