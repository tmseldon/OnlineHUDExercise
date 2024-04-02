// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeExtended.generated.h"

UCLASS()
class ONLINEHUDEXERCISE_API UEncapsulatePlayerData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerData)
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerData)
	FName Nickname;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerData)
	int Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerData)
	UTexture2D* ProfilePic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FDateTime LastSeen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FDateTime RecentConnection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	bool bIsOnline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FText BioInfo;

	void HydratePlayerDataModel(struct FPlayerProfileData& InitialData);

	void UpdatePlayerDataModelTime(bool bUpdateTimeReConnection);
};



/**
 * 
 */
DECLARE_DELEGATE(FOnModelCreated);
DECLARE_DELEGATE_ThreeParams(FOnPlayerStatusChanged, FString, bool, UEncapsulatePlayerData*);

UCLASS()
class ONLINEHUDEXERCISE_API AGameModeExtended : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initial Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* InitialPlayersStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection Simulation", meta = (AllowPrivateAccess = "true"))
	bool bIsTurnOnSimulation = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection Simulation", meta = (AllowPrivateAccess = "true"))
	int ChangeConnectionRangeSecondsMin = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection Simulation", meta = (AllowPrivateAccess = "true"))
	int ChangeConnectionRangeSecondsMax = 8;

	UPROPERTY()
	TArray<class UEncapsulatePlayerData*> PlayersOnline;

	UPROPERTY()
	TArray<class UEncapsulatePlayerData*> PlayersOffline;

	FTimerHandle ChangingStatusTimerHandle;

	void CreateInitialModel();

	void StartStatusChangeSimulation();

	int GetRandomTimeChangeStatus();


public:

	AGameModeExtended();

	
	FOnModelCreated OnPlayerDataModelHydrated;
	FOnPlayerStatusChanged OnPlayerDataHasChanged;


	UFUNCTION()
	TArray<UEncapsulatePlayerData*> GetOnlinePlayers() const;

	UFUNCTION()
	TArray<UEncapsulatePlayerData*> GetOfflinePlayers() const;
};
