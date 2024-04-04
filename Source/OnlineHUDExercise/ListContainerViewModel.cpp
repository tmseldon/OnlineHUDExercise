// Fill out your copyright notice in the Description page of Project Settings.


#include "ListContainerViewModel.h"
#include "GameModeExtended.h"
#include "HUDManager.h"
#include "PlayerCardExtended.h"
#include "PlayerCardViewModel.h"
#include "TooltipViewModel.h"
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
	UPlayerCardExtended* NewPlayerCardWidget)
{
	if (NewPlayerCardVM == nullptr || NewPlayerCardWidget == nullptr)
	{
		return;
	}

	ListPlayersCardViewModels.Add(NewPlayerCardVM);
	MapPlayersCards.Add(NewPlayerCardVM, NewPlayerCardWidget);

	//UE_LOG(LogTemp, Warning, TEXT("Checking ListPlayerCardsVM: %d same as MaxPerScreen: %d"),
	//	ListPlayersCardViewModels.Num(), NumberCardsperScreen);
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
		UE_LOG(LogTemp, Warning, TEXT("el numero de paginas es %f"), MaxPageValue);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MaxPageValue);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CheckSliderEnable);
	}
}

bool UListContainerViewModel::CheckSliderEnable() const
{
	if (MaxPageValue <= 0)
	{
		return false;
	}
	return true;
}

void UListContainerViewModel::OnTitleButtonPress()
{
	switch (ListVisibilityStatus)
	{
	case ESlateVisibility::Visible:
		SetListVisibilityStatus(ESlateVisibility::Hidden);
		break;

	case ESlateVisibility::Hidden:
		UpdatePlayerList();
		SetListVisibilityStatus(ESlateVisibility::Visible);
		DrawActiveScreen();
		break;
	}
}

int UListContainerViewModel::GetCurrentTopIndex() const
{
	return CurrentActivePageValue * NumberCardsperScreen;
}

void UListContainerViewModel::DrawActiveScreen()
{
	// CurrentActivePage was updated and we call this method
	// We calculate the top index player card
	TopIndexOnActivePage = GetCurrentTopIndex();
	/*UE_LOG(LogTemp, Warning, TEXT("Top Index: %f"), CurrentActivePageValue);*/

	//UpdatePlayerList();

	// Recalculate the max amount of pages just in case
	if (NumberCardsperScreen > 0)
	{
		float TotalPagesList = FMath::DivideAndRoundUp(ListPlayerData.Num(), NumberCardsperScreen) - 1;
		
		// If the number of pages is reduced, and we are in a page that will disappear, 
		// better to force the list go to the first page (for safety)
		if (CurrentActivePageValue > TotalPagesList)
		{
			CurrentActivePageValue = 0;
			TopIndexOnActivePage = 0;

			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CurrentActivePageValue);
		}

		/*UE_LOG(LogTemp, Warning, TEXT("Totla pages: %f"), TotalPagesList);*/

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
				UE_LOG(LogTemp, Warning, TEXT("agregando anuimacion visible aca en indice %d"), IndexPlayerCardVM - TopIndexOnActivePage);
				ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
					->SetCardVisibilityStatus(ESlateVisibility::Visible);
			}

			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->AddDataIntoCard(ListPlayerData[IndexPlayerCardVM]);
		}
		else
		{
			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetCardVisibilityStatus(ESlateVisibility::Hidden);
		}
	}
}

void UListContainerViewModel::OnPlayerHasChangedEventHandler(FString NickName, UEncapsulatePlayerData* PlayerData, EListMode PlayerNewMode)
{

	/* For debugging
	*/
	FString TextEnum = UEnum::GetValueAsString(PlayerNewMode);
	FString ListModeEnum = UEnum::GetValueAsString(CurrentListMode);
	UE_LOG(LogTemp, Warning, TEXT("enum en evento es: %s y este listado es: %s"), *TextEnum, *ListModeEnum);
	/*
	*/

	if (PlayerData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning the player data is null we are not going to update the list"));
		return;
	}

	// if the player has changed to this same list mode, it means we need to add the new player to the list
	if (PlayerNewMode == CurrentListMode && FindIndexPlayerData(NickName) == -1)
	{
		if (PlayerNewMode == EListMode::Online)
		{
			if (CurrentActivePageValue == 0)
			{
				UPlayerCardViewModel* CurrentVM = ListPlayersCardViewModels[0];
				UPlayerCardExtended* CurrentWidget = MapPlayersCards[CurrentVM];
				CurrentWidget->TriggerFXOnPlayerCard(-1, EPlayerCardAnim::Online);
			}
			ListPlayerData.Insert(PlayerData, 0);
		}
		else
		{
			ListPlayerData.Add(PlayerData);
		}
		
		DrawActiveScreen();
		return;
	}

	// if the player has changed to the other mode, we need to check if it is in the list and remove it
	if (PlayerNewMode != CurrentListMode)
	{
		int IndexPlayerOnList = FindIndexPlayerData(NickName);
		if (IndexPlayerOnList != -1)
		{
			// we need to check if the index is on the current active screen
			if (CheckIndexPlayerIsOnScreen(IndexPlayerOnList))
			{
				// if the player is looking the index
				//make some animation/visual change
				int ViewModelIndex = IndexPlayerOnList % NumberCardsperScreen;
				UPlayerCardViewModel* CurrentVM = ListPlayersCardViewModels[ViewModelIndex];
				UPlayerCardExtended* CurrentWidget = MapPlayersCards[CurrentVM];

				if (CurrentListMode == EListMode::Online)
				{
					CurrentWidget->TriggerFXOnPlayerCard(IndexPlayerOnList, EPlayerCardAnim::Disconnected);
				}
				else
				{
					CurrentWidget->TriggerFXOnPlayerCard(IndexPlayerOnList, EPlayerCardAnim::FadeOut);
				}
			}
			else
			{
				SafeRemovePlayerAtIndex(IndexPlayerOnList);
				DrawActiveScreen();
			}
		}
	}

}

void UListContainerViewModel::CallbackAnimation(int IndexPlayer)
{
	SafeRemovePlayerAtIndex(IndexPlayer);
	DrawActiveScreen();
}

int UListContainerViewModel::FindIndexPlayerData(FString NickName)
{
	int IndexNicknameOnList = ListPlayerData.IndexOfByPredicate([NickName](const UEncapsulatePlayerData* PlayerData)
	{
		return PlayerData->Nickname == NickName;
	});

	return IndexNicknameOnList;
}

bool UListContainerViewModel::CheckIndexPlayerIsOnScreen(int PlayerIndex)
{
	int MinIndex = GetCurrentTopIndex();
	int MaxIndex = MinIndex + NumberCardsperScreen - 1;

	if (PlayerIndex >= MinIndex && PlayerIndex <= MaxIndex)
	{
		return true;
	}

	return false;
}

void UListContainerViewModel::SafeRemovePlayerAtIndex(int PlayerIndex)
{
	if (ListPlayerData.Num() == 1)
	{
		ListPlayerData.Reset();
	}
	else
	{
		ListPlayerData.RemoveAt(PlayerIndex);
	}
}

void UListContainerViewModel::InjectTooltipViewModelToCards(UTooltipViewModel* TooltipVM)
{
	for (UPlayerCardViewModel* PlayerCard : ListPlayersCardViewModels)
	{
		if (PlayerCard != nullptr)
		{
			PlayerCard->SetTooltipVMReference(TooltipVM);
		}
	}
}