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

	GetWorldTimerManager().SetTimer(
		ChangingStatusTimerHandle, 
		this, 
		&AGameModeExtended::StartStatusChangeSimulation, 
		InitialRandomTime, 
		true, 
		0
	);
}

void AGameModeExtended::CreateInitialModel()
{
	if (InitialPlayersStatus != nullptr)
	{
		TArray<FPlayerProfileData*> AllRowsInfo;
		InitialPlayersStatus->GetAllRows(FString(TEXT("InitialData")), AllRowsInfo);
		int TotalElements = AllRowsInfo.Num();

		for (int Index = 0; Index < TotalElements; Index++)
		{
			FPlayerProfileData ValueData = *AllRowsInfo[Index];

			UEncapsulatePlayerData* DataEncapsulated = NewObject<UEncapsulatePlayerData>();
			DataEncapsulated->HydratePlayerDataModel(ValueData);

			if (ValueData.bIsOnline)
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
}

int AGameModeExtended::GetRandomTimeChangeStatus()
{
	return FMath::RandRange(ChangeConnectionRangeSecondsMin, ChangeConnectionRangeSecondsMax);
}

void AGameModeExtended::StartStatusChangeSimulation()
{
	// We determine if we change someone from Offline (0) or Online (1)
	int ChangeStatus = FMath::RandRange(0, 1);

	FString UserChanged;
	bool bChangedStatus;

	int ChangeStatusPlayerIndex;

	if (ChangeStatus == 0)
	{
		int PlayerOfflineTotal = PlayersOffline.Num() - 1;

		if (PlayerOfflineTotal >= 0)
		{
			ChangeStatusPlayerIndex = FMath::RandRange(0, PlayerOfflineTotal);
			PlayersOffline[ChangeStatusPlayerIndex]->bIsOnline = true;

			// Debugging
			UserChanged = PlayersOffline[ChangeStatusPlayerIndex]->Nickname.ToString();
			bChangedStatus = PlayersOffline[ChangeStatusPlayerIndex]->bIsOnline;
			UE_LOG(LogTemp, Warning, TEXT("Cambio de usuario: %s al status %s"),
				*UserChanged, bChangedStatus ? TEXT("a ONLINE") : TEXT("a OFFLINE"));

			//UEncapsulatePlayerData* DataEncapsulated = NewObject<UEncapsulatePlayerData>();
			//DataEncapsulated->HydratePlayerDataModel(*PlayersOffline[ChangeStatusPlayerIndex], true);

			//PlayersOnline.Add(DataEncapsulated);

			PlayersOnline.Add(PlayersOffline[ChangeStatusPlayerIndex]);

			if (PlayerOfflineTotal > 0)
			{
				PlayersOffline.RemoveAt(ChangeStatusPlayerIndex);
			}
			else
			{
				PlayersOffline.Reset();
			}
			
		}
	}
	else
	{
		int PlayersOnlineTotal = PlayersOnline.Num() - 1;

		if (PlayersOnlineTotal >= 0)
		{
			ChangeStatusPlayerIndex = FMath::RandRange(0, PlayersOnlineTotal);
			PlayersOnline[ChangeStatusPlayerIndex]->bIsOnline = false;

			// Debugging
			UserChanged = PlayersOnline[ChangeStatusPlayerIndex]->Nickname.ToString();
			bChangedStatus = PlayersOnline[ChangeStatusPlayerIndex]->bIsOnline;
			UE_LOG(LogTemp, Warning, TEXT("Cambio de usuario: %s al status %s"),
				*UserChanged, bChangedStatus ? TEXT("a ONLINE") : TEXT("a OFFLINE"));


			//UEncapsulatePlayerData* DataEncapsulated = NewObject<UEncapsulatePlayerData>();
			//DataEncapsulated->HydratePlayerDataModel(*PlayersOnline[ChangeStatusPlayerIndex], true);

			//PlayersOffline.Add(DataEncapsulated);

			PlayersOffline.Add(PlayersOnline[ChangeStatusPlayerIndex]);

			if (PlayersOnlineTotal > 1)
			{
				PlayersOnline.RemoveAt(ChangeStatusPlayerIndex);
			}
			else
			{
				PlayersOnline.Reset();
			}
		}
	}

	//Debugging

	// ONLINE

	for (UEncapsulatePlayerData* Data : PlayersOnline)
	{
		FString Nick = Data->Nickname.ToString();
		UE_LOG(LogTemp, Warning, TEXT("Usuario online: %s"), *Nick);
	}

	UE_LOG(LogTemp, Warning, TEXT("================="));

	//OFFLINE

	for (UEncapsulatePlayerData* Data : PlayersOffline)
	{
		FString Nick = Data->Nickname.ToString();
		UE_LOG(LogTemp, Warning, TEXT("Usuario offline: %s"), *Nick);
	}


	//float NewRandomTime = GetRandomTimeChangeStatus();

	//UE_LOG(LogTemp, Warning, TEXT("nuevo intervalo de tiempo es: %f"), NewRandomTime);

	////FTimerHandle ChangingStatusTimerHandle;
	//GetWorldTimerManager().SetTimer(
	//	ChangingStatusTimerHandle,
	//	this,
	//	&AGameModeExtended::StartStatusChangeSimulation,
	//	NewRandomTime,
	//	false,
	//	0
	//);
}