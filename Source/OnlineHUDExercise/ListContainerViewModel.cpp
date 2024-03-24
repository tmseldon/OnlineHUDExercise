// Fill out your copyright notice in the Description page of Project Settings.


#include "ListContainerViewModel.h"
#include "GameModeExtended.h"
#include "HUDManager.h"
#include "PlayerCardViewModel.h"
#include "Blueprint/UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "Kismet/GameplayStatics.h"


void UListContainerViewModel::InitializeViewModel(AHUDManager* HUDReference, EListMode Mode, int NumberCards)
{
	if (HUDReference == nullptr)
	{
		return;
	}

	HudManager = HUDReference;
	CurrentListMode = Mode;
	NumberCardsperScreen = NumberCards;

	switch (CurrentListMode)
	{
	case EListMode::Online:
		ListPlayerData = HudManager->GetUpdatedListOnline();
		break;
	case EListMode::Offline:
		ListPlayerData = HudManager->GetUpdatedListOffline();
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("el tamaño del listado es: %d"), ListPlayerData.Num());
}

void UListContainerViewModel::AddCardPlayerReferencesToList(
	UPlayerCardViewModel* NewPlayerCardVM, 
	UUserWidget* NewPlayerCardWidget)
{
	if (NewPlayerCardVM == nullptr || NewPlayerCardWidget == nullptr)
	{
		return;
	}

	ListPlayersCardViewModels.Add(NewPlayerCardVM);
	MapPlayersCards.Add(NewPlayerCardVM, NewPlayerCardWidget);

	UE_LOG(LogTemp, Warning, TEXT("Checking ListPlayerCardsVM: %d same as MaxPerScreen: %d"),
		ListPlayersCardViewModels.Num(), NumberCardsperScreen);
}

ESlateVisibility UListContainerViewModel::GetListVisibilityStatus() const
{
	return ListVisibilityStatus;
}


void UListContainerViewModel::SetListVisibilityStatus(ESlateVisibility NewStatusList)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(ListVisibilityStatus, NewStatusList))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ListVisibilityStatus);
	}
}

void UListContainerViewModel::OnTitleButtonPress()
{
	switch (ListVisibilityStatus)
	{
	case ESlateVisibility::Visible:
		SetListVisibilityStatus(ESlateVisibility::Hidden);
		break;

	case ESlateVisibility::Hidden:
		SetListVisibilityStatus(ESlateVisibility::Visible);
		break;
	}
}

void UListContainerViewModel::DrawActiveScreen()
{
	// identificar en qué página de la lista estamos mostrando

	// tomar la informacion sobre esa pagina, tomando como indicador el index top 

	// rellenar los ViewModels con la nueva info


	UE_LOG(LogTemp, Warning, TEXT("el tamaño del listado de jugadores en DRAW: %d"), ListPlayerData.Num());
	UE_LOG(LogTemp, Warning, TEXT("el tamaño del listado de VM en DRAW: %d"), ListPlayersCardViewModels.Num());


	for (int IndexPlayerCardVM = 0; IndexPlayerCardVM < NumberCardsperScreen; IndexPlayerCardVM++)
	{
		if (ListPlayerData.IsValidIndex(IndexPlayerCardVM))
		{
			ListPlayersCardViewModels[IndexPlayerCardVM]
				->SetNameField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Name));
			ListPlayersCardViewModels[IndexPlayerCardVM]
				->SetAliasField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Nickname));
		}
		else
		{
			// we need to clear the player card
			// need to add a binder to control visibility

			ListPlayersCardViewModels[IndexPlayerCardVM]
				->SetNameField(FText::FromString(TEXT("vacio por ahora")));
			ListPlayersCardViewModels[IndexPlayerCardVM]
				->SetAliasField(FText::FromString(TEXT("vacio por ahora")));

		}
	}
	
}