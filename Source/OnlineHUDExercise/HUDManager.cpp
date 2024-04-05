// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"
#include "GameModeExtended.h"
#include "ListPlayerExtended.h"
#include "PlayerCardViewModel.h"
#include "MVVMSubsystem.h"
#include "ToastMessageViewModel.h"
#include "Blueprint/UserWidget.h"
#include "View/MVVMView.h" 

void AHUDManager::BeginPlay()
{

	//Initialize before execute the BluePrint part of this method
	//We get all the important dependencies here

	GameModeExtendedService = Cast<AGameModeExtended>(GetWorld()->GetAuthGameMode());
	if (GameModeExtendedService != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD MANAGER initiated!!"));
		GameModeExtendedService->OnPlayerDataHasChanged.BindUObject(this, &AHUDManager::OnChangeData);
		CreatePlayerStatusLists();
	}

	CharacterController = this->GetOwningPlayerController();
	if (CharacterController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterController is null, there is a problem trying to get the reference at HUD"))
	}

	Super::BeginPlay();
}

void AHUDManager::CreatePlayerStatusLists()
{
	OnlinePlayerList = GameModeExtendedService->GetOnlinePlayers();
	OfflinePlayerList = GameModeExtendedService->GetOfflinePlayers();

	UE_LOG(LogTemp, Warning, TEXT("The size for the online is on the HUD is: %d"), OnlinePlayerList.Num());
	UE_LOG(LogTemp, Warning, TEXT("The size for the offline is on the HUD is: %d"), OfflinePlayerList.Num());
}

TArray<UEncapsulatePlayerData*> AHUDManager::GetUpdatedListOnline()
{
	OnlinePlayerList = GameModeExtendedService->GetOnlinePlayers();
	UE_LOG(LogTemp, Warning, TEXT("Returning he size for the online is on the HUD is: %d"), OnlinePlayerList.Num());
	return OnlinePlayerList;
}

TArray<UEncapsulatePlayerData*> AHUDManager::GetUpdatedListOffline()
{
	OfflinePlayerList = GameModeExtendedService->GetOfflinePlayers();
	UE_LOG(LogTemp, Warning, TEXT("Returning the size for the offline is on the HUD is: %d"), OfflinePlayerList.Num());
	return OfflinePlayerList;
}

void AHUDManager::OnChangeData(FString NicknamePlayer, bool bOnlineStatus, UEncapsulatePlayerData* PlayerData)
{
	OnReceivingPlayerData(FName(*NicknamePlayer), bOnlineStatus, PlayerData);
	EListMode NewListMode = (bOnlineStatus == true) ? EListMode::Online : EListMode::Offline;

	OnPlayerHasChangedDataEvent.Broadcast(NicknamePlayer, PlayerData, NewListMode);
}

void AHUDManager::CallPlayerOnlineStatusScreen()
{
	// If the online menu has not been created, we start the widget here
	if (OnlineScreenSpawnedWidget == nullptr)
	{
		OnlineScreenSpawnedWidget = CreateWidget(
			CharacterController,
			OnlineScreenWidget,
			FName(TEXT("Player Online Status Screen"))
		);

		if (OnlineScreenSpawnedWidget != nullptr)
		{
			OnlineScreenSpawnedWidget->AddToViewport();
			CharacterController->SetInputMode(FInputModeUIOnly());
			CharacterController->bShowMouseCursor = true;
		}
	}
	else
	{
		// Here we switched between Visible and Hidden if the menu online widget has been created
		// We set the input mode accordingly to the UI or Gameplay
		// NOTE: added additional cases for future testing
		ESlateVisibility CurrentVisbility = OnlineScreenSpawnedWidget->GetVisibility();
		switch (CurrentVisbility)
		{
		case ESlateVisibility::Hidden:
		case ESlateVisibility::Collapsed:
			OnlineScreenSpawnedWidget->SetVisibility(ESlateVisibility::Visible);
			CharacterController->SetInputMode(FInputModeUIOnly());
			CharacterController->bShowMouseCursor = true;
			break;

		case ESlateVisibility::Visible:
		default:
			OnlineScreenSpawnedWidget->SetVisibility(ESlateVisibility::Hidden);
			CharacterController->SetInputMode(FInputModeGameOnly());
			CharacterController->bShowMouseCursor = false;
			break;
		}
	}
}