// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListContainerViewModel.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"

/**
 * HUD Manager serves as a bridge between the simulated online service and the different widgets for the HUD
 * It broadcast the changes through a Multicast Delegate. We "assume" that the nickname is unique and serves as the
 * player identification
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerDataChangesEvent, FString, NickName, class UEncapsulatePlayerData*, PlayerData, EListMode, CurrentMode);

UCLASS()
class ONLINEHUDEXERCISE_API AHUDManager : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDataChangesEvent OnPlayerHasChangedDataEvent;

	TArray<class UEncapsulatePlayerData*> GetUpdatedListOnline();
	TArray<class UEncapsulatePlayerData*> GetUpdatedListOffline();

	// Callback for calling the Online Menu
	UFUNCTION(BlueprintCallable)
	void CallPlayerOnlineStatusScreen();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Event for BP if we need make something on BP from HUD Manager
	UFUNCTION(BlueprintImplementableEvent)
	void OnReceivingPlayerData(FName NickNamePlayer, bool bOnlineStatus, class UEncapsulatePlayerData* PlayerData);
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OnlineScreenWidget;

	// Reference for the widget that holds all the menu screen, this is the one created at init
	UUserWidget* OnlineScreenSpawnedWidget;

	// Reference for the Player Controller
	APlayerController* CharacterController;

	// Reference for the Game Mode Extended 
	class AGameModeExtended* GameModeExtendedService;

	//Lists of players with extra info
	TArray<class UEncapsulatePlayerData*> OnlinePlayerList;
	TArray<class UEncapsulatePlayerData*> OfflinePlayerList;

	// Delegate to listen changes on GameModeExtended
	void OnChangeData(FString NicknamePlayer, bool bOnlineStatus, class UEncapsulatePlayerData* PlayerData);

	// Method to create the list of players
	void CreatePlayerStatusLists();
};
