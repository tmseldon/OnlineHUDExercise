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

	// Recalculate the max amount of pages just in case
	if (NumberCardsperScreen > 0)
	{
		float TotalPagesList = FMath::DivideAndRoundUp(ListPlayerData.Num(), NumberCardsperScreen) - 1;
		
		//if (CurrentActivePageValue > TotalPagesList)
		//{
		//	CurrentActivePageValue = TotalPagesList;
		//}

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