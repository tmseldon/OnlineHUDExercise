// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeExtended.h"
#include "PlayerProfileData.h"
#include "OnlineHUDExerciseCharacter.h"
#include "UObject/ConstructorHelpers.h"


UEncapsulatePlayerData::UEncapsulatePlayerData()
{
	
}

void UEncapsulatePlayerData::HydratePlayerDataModel(FPlayerProfileData& InitialData)
{
	Name = InitialData.Name;
	Nickname = InitialData.Nickname;
	Level = InitialData.Level;
	ProfilePic = InitialData.ProfilePic;
	LastSeen = InitialData.LastSeen;
	bIsOnline = InitialData.bIsOnline;
}

void UEncapsulatePlayerData::HydratePlayerDataModel(UEncapsulatePlayerData& UpdatedData, bool bUpdateTimeConnection)
{
	Name = UpdatedData.Name;
	Nickname = UpdatedData.Nickname;
	Level = UpdatedData.Level;
	ProfilePic = UpdatedData.ProfilePic;
	LastSeen = UpdatedData.LastSeen;
	bIsOnline = UpdatedData.bIsOnline;

	if (bUpdateTimeConnection)
	{
		RecentChangeConnection = FDateTime::Now();
	}
}


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

TArray<UEncapsulatePlayerData*> AGameModeExtended::GetOnlinePlayers() const
{
	return PlayersOnline;
}

TArray<UEncapsulatePlayerData*> AGameModeExtended::GetOfflinePlayers() const
{
	return PlayersOffline;
}

void AGameModeExtended::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialModel();

	float InitialRandomTime = GetRandomTimeChangeStatus();

	UE_LOG(LogTemp, Warning, TEXT("primer intervalo de tiempo es: %f"), InitialRandomTime);

	//Remove comments, putting like this for testing list
	if (bIsTurnOnSimulation)
	{
		GetWorldTimerManager().SetTimer(
			ChangingStatusTimerHandle,
			this,
			&AGameModeExtended::StartStatusChangeSimulation,
			InitialRandomTime,
			true,
			0
		);
	}
}

void AGameModeExtended::CreateInitialModel()
{
	if (InitialPlayersStatus != nullptr)
	{
		TArray<FPlayerProfileData*> AllRowsInfo;
		InitialPlayersStatus->GetAllRows(FString(TEXT("InitialData")), AllRowsInfo);

		for (FPlayerProfileData* PlayerData : AllRowsInfo)
		{
			UEncapsulatePlayerData* DataEncapsulated = NewObject<UEncapsulatePlayerData>();
			DataEncapsulated->HydratePlayerDataModel(*PlayerData);

			if (PlayerData->bIsOnline)
			{
				PlayersOnline.Add(DataEncapsulated);
			}
			else
			{
				PlayersOffline.Add(DataEncapsulated);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Cantidad de jugadores offline: %d"), PlayersOffline.Num());
	UE_LOG(LogTemp, Warning, TEXT("Cantidad de jugadores online: %d"), PlayersOnline.Num());

	OnPlayerDataModelHydrated.ExecuteIfBound();
}

int AGameModeExtended::GetRandomTimeChangeStatus()
{
	return FMath::RandRange(ChangeConnectionRangeSecondsMin, ChangeConnectionRangeSecondsMax);
}

void AGameModeExtended::StartStatusChangeSimulation()
{
	// We determine if we change someone from Offline (0) or Online (1)
	int ChangeStatus = FMath::RandRange(0, 1);

	// Changed information to send on the event
	// We are asuming that nicknames are unique
	FString NicknameChangeStatus;
	bool bChangedStatus = false;
	int ChangeStatusPlayerIndex = -1;

	//Case changing someone from Offline to Online
	if (ChangeStatus == 0)
	{
		if (PlayersOffline.Num() > 0)
		{
			ChangeStatusPlayerIndex = FMath::RandRange(0, PlayersOffline.Num() - 1);
			PlayersOffline[ChangeStatusPlayerIndex]->bIsOnline = true;

			NicknameChangeStatus = PlayersOffline[ChangeStatusPlayerIndex]->Nickname.ToString();
			bChangedStatus = PlayersOffline[ChangeStatusPlayerIndex]->bIsOnline;

			//// Debugging
			//UE_LOG(LogTemp, Warning, TEXT("*****************"));
			//UE_LOG(LogTemp, Warning, TEXT("Cambio de usuario: %s al status %s"),
			//	*NicknameChangeStatus, bChangedStatus ? TEXT("a ONLINE") : TEXT("a OFFLINE"));

			PlayersOnline.Add(PlayersOffline[ChangeStatusPlayerIndex]);

			if (PlayersOffline.Num() > 1)
			{
				PlayersOffline.RemoveAt(ChangeStatusPlayerIndex);
			}
			else
			{
				PlayersOffline.Reset();
			}
		}
	}

	//Case changing someone from Online to Offline
	else
	{
		if (PlayersOnline.Num() > 0)
		{
			ChangeStatusPlayerIndex = FMath::RandRange(0, PlayersOnline.Num() - 1);
			PlayersOnline[ChangeStatusPlayerIndex]->bIsOnline = false;

			NicknameChangeStatus = PlayersOnline[ChangeStatusPlayerIndex]->Nickname.ToString();
			bChangedStatus = PlayersOnline[ChangeStatusPlayerIndex]->bIsOnline;

			//// Debugging
			//UE_LOG(LogTemp, Warning, TEXT("*****************"));
			//UE_LOG(LogTemp, Warning, TEXT("Cambio de usuario: %s al status %s"),
			//	*NicknameChangeStatus, bChangedStatus ? TEXT("a ONLINE") : TEXT("a OFFLINE"));

			PlayersOffline.Add(PlayersOnline[ChangeStatusPlayerIndex]);

			if (PlayersOnline.Num() > 1)
			{
				PlayersOnline.RemoveAt(ChangeStatusPlayerIndex);
			}
			else
			{
				PlayersOnline.Reset();
			}
		}
	}

	if (ChangeStatusPlayerIndex != -1)
	{
		// Trigger event that somedata has changed for the players
		OnPlayerDataHasChanged.ExecuteIfBound(NicknameChangeStatus, bChangedStatus, ChangeStatusPlayerIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No change on connection emulated"));
	}


	////Debugging

	//// ONLINE

	//for (UEncapsulatePlayerData* Data : PlayersOnline)
	//{
	//	FString Nick = Data->Nickname.ToString();
	//	UE_LOG(LogTemp, Warning, TEXT("Usuario online: %s"), *Nick);
	//}

	//UE_LOG(LogTemp, Warning, TEXT("================="));

	////OFFLINE

	//for (UEncapsulatePlayerData* Data : PlayersOffline)
	//{
	//	FString Nick = Data->Nickname.ToString();
	//	UE_LOG(LogTemp, Warning, TEXT("Usuario offline: %s"), *Nick);
	//}
}