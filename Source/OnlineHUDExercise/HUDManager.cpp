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

	GameModeExtendedService = Cast<AGameModeExtended>(GetWorld()->GetAuthGameMode());
	if (GameModeExtendedService != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD MANAGER iniciado!!"));
		GameModeExtendedService->OnPlayerDataHasChanged.BindUObject(this, &AHUDManager::OnChangeData);
		CreatePlayerStatusLists();
	}

	Super::BeginPlay();
}

void AHUDManager::CreatePlayerStatusLists()
{
	OnlinePlayerList = GameModeExtendedService->GetOnlinePlayers();
	OfflinePlayerList = GameModeExtendedService->GetOfflinePlayers();

	UE_LOG(LogTemp, Warning, TEXT("el tamanyoo del listado online ne HUD es: %d"), OnlinePlayerList.Num());
	UE_LOG(LogTemp, Warning, TEXT("el tamanyoo del listado offline ne HUD es: %d"), OfflinePlayerList.Num());
}

TArray<UEncapsulatePlayerData*> AHUDManager::GetUpdatedListOnline()
{
	OnlinePlayerList = GameModeExtendedService->GetOnlinePlayers();
	//need to add extra info here before returning list
	UE_LOG(LogTemp, Warning, TEXT("REtornando el tamanyoo del listado online ne HUD es: %d"), OnlinePlayerList.Num());
	return OnlinePlayerList;
}

TArray<UEncapsulatePlayerData*> AHUDManager::GetUpdatedListOffline()
{
	OfflinePlayerList = GameModeExtendedService->GetOfflinePlayers();
	//need to add extra info here before returning list
	UE_LOG(LogTemp, Warning, TEXT("REtornando el tamanyoo del listado offline ne HUD es: %d"), OfflinePlayerList.Num());
	return OfflinePlayerList;
}


void AHUDManager::TestingHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("called from constructor VM here"));
}


void AHUDManager::OnChangeData(FString NicknamePlayer, bool bOnlineStatus, int OldIndex)
{
	// BluepreintEvent (este es para pruebas en donde se cambia estado de player card desde BP)
	OnReceivingPlayerData(FName(*NicknamePlayer), bOnlineStatus, OldIndex);

	if (NewToastVM != nullptr)
	{
		//Nota HUD manager no deberia tener esta referencia, deberia ser al reves
		// Esto para testeo por mientras
		NewToastVM->TriggerToastMessage(ESlateVisibility::Visible, NicknamePlayer, FString::FromInt(OldIndex));
	}

	EListMode NewListMode = (bOnlineStatus == true) ? EListMode::Online : EListMode::Offline;
	OnPlayerHasChangedDataEvent.Broadcast(NicknamePlayer, OldIndex, NewListMode);
}

//Nota HUD manager no deberia tener esta referencia, deberia ser al reves
		// Esto para testeo por mientras
void AHUDManager::SetToastVMReference(UToastMessageViewModel* ReferenceVM)
{
	NewToastVM = ReferenceVM;
}
