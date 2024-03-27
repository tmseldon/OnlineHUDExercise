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
	UpdatePlayerList();

	UE_LOG(LogTemp, Warning, TEXT("el tamaño del listado es: %d"), ListPlayerData.Num());

	/*HudManager->OnPlayerHasChangedDataEvent.RemoveDynamic(this, &UListContainerViewModel::OnPlayerHasChangedEventHandler);*/
	HudManager->OnPlayerHasChangedDataEvent.AddDynamic(this, &UListContainerViewModel::OnPlayerHasChangedEventHandler);
}

void UListContainerViewModel::UpdatePlayerList()
{
	switch (CurrentListMode)
	{
	case EListMode::Online:
		ListPlayerData = HudManager->GetUpdatedListOnline();
		break;
	case EListMode::Offline:
		ListPlayerData = HudManager->GetUpdatedListOffline();
		break;
	}
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

float UListContainerViewModel::GetCurrentActivePageValue() const
{
	return CurrentActivePageValue;
}

void UListContainerViewModel::SetCurrentActivePageValue(float NewValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentActivePageValue, NewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CurrentActivePageValue);
		DrawActiveScreen();
	}
}

float UListContainerViewModel::GetMaxPageValue() const
{
	return MaxPageValue;
}

void UListContainerViewModel::SetMaxPageValue(float NewValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxPageValue, NewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MaxPageValue);
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
	// CurrentActivePage was updated and we call this method
	// We calculate the top index player card
	TopIndexOnActivePage = CurrentActivePageValue * NumberCardsperScreen;
	UE_LOG(LogTemp, Warning, TEXT("Top Index: %f"), CurrentActivePageValue);

	UpdatePlayerList();

	// Recalculate the max amount of pages just in case
	if (NumberCardsperScreen > 0)
	{
		float TotalPagesList = FMath::DivideAndRoundUp(ListPlayerData.Num(), NumberCardsperScreen) - 1;
		
		// If the number of pages is reduced, and we are in a page that will disappear, 
		// better to force the list go to the new last page (for safety)
		if (CurrentActivePageValue > TotalPagesList)
		{
			CurrentActivePageValue = TotalPagesList;
			TopIndexOnActivePage = CurrentActivePageValue * NumberCardsperScreen;

			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CurrentActivePageValue);
		}

		UE_LOG(LogTemp, Warning, TEXT("Totla pages: %f"), TotalPagesList);

		SetMaxPageValue(TotalPagesList);
	}

	for (int IndexPlayerCardVM = TopIndexOnActivePage; 
		IndexPlayerCardVM < NumberCardsperScreen + TopIndexOnActivePage;
		IndexPlayerCardVM++)
	{
		if (ListPlayerData.IsValidIndex(IndexPlayerCardVM))
		{
			if (ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->GetCardVisibilityStatus() == ESlateVisibility::Hidden)
			{
				ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
					->SetCardVisibilityStatus(ESlateVisibility::Visible);
			}

			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetNameField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Name));
			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetAliasField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Nickname));
		}
		else
		{
			// we need to clear the player card
			// need to add a binder to control visibility

			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetCardVisibilityStatus(ESlateVisibility::Hidden);

		}
	}
	
}

void UListContainerViewModel::OnPlayerHasChangedEventHandler(FString NickName, int OldIndex, EListMode CurrentMode)
{
	if (CurrentMode == CurrentListMode)
	{
		// Add here some BP event for animation or delay?

		DrawActiveScreen();
	}
	else
	{
		// we need to determine if the player is seeing the screen where the player has changed os state

		//if that is the case, we need to create a animation or graphical effect on the player and
		//update the list

		// if it is not on the screen where the player is, just Redraw
	}
}