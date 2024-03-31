// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListContainerViewModel.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerDataChangesEvent, FString, NickName, class UEncapsulatePlayerData*, PlayerData, EListMode, CurrentMode);

UCLASS()
class ONLINEHUDEXERCISE_API AHUDManager : public AHUD
{
	GENERATED_BODY()
	
private:

	//Borrar este
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	int NumberPlayerCardVMOnPool = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OnlineScreenWidget;

	//Borrar este
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ListContainerWidget;

	//Borrar este
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerCardWidget;

	//Borrar este
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ToastMessageWidget;


	// Reference for the Player Controller
	APlayerController* CharacterController;

	// Reference for the Game Mode Extended 
	class AGameModeExtended* GameModeExtendedService;

	//Lists of players with extra info
	TArray<class UEncapsulatePlayerData*> OnlinePlayerList;
	TArray<class UEncapsulatePlayerData*> OfflinePlayerList;



	//Borrar este
	class UToastMessageViewModel* NewToastVM;

	//Borrar este
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Card Components", meta = (AllowPrivateAccess = "true"))
	TArray<class UUserWidget*> ListSpawnedPlayerCardsWidgets;

	// Delegate to listen changes on GameModeExtended
	void OnChangeData(FString NicknamePlayer, bool bOnlineStatus, class UEncapsulatePlayerData* PlayerData);

	void CreatePlayerStatusLists();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Event for BP if we need make something on BP from HUD Manager
	UFUNCTION(BlueprintImplementableEvent)
	void OnReceivingPlayerData(FName NickNamePlayer, bool bOnlineStatus, class UEncapsulatePlayerData* PlayerData);

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDataChangesEvent OnPlayerHasChangedDataEvent;


	//Borrar este
	UFUNCTION(BlueprintCallable)
	void SetToastVMReference(UToastMessageViewModel* ReferenceVM);

	TArray<class UEncapsulatePlayerData*> GetUpdatedListOnline();
	TArray<class UEncapsulatePlayerData*> GetUpdatedListOffline();

	//Borrar este
	void TestingHUD();

};
