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
	/*UE_LOG(LogTemp, Warning, TEXT("Top Index: %f"), CurrentActivePageValue);*/

	//UpdatePlayerList();

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
				->SetNameField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Name));
			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetAliasField(FText::FromName(ListPlayerData[IndexPlayerCardVM]->Nickname));
		}
		else
		{
			// we need to clear the player card
			// need to add a binder to control visibility
			UE_LOG(LogTemp, Warning, TEXT("agregando anuimacion descartar aca en indice %d"), IndexPlayerCardVM - TopIndexOnActivePage);

			ListPlayersCardViewModels[IndexPlayerCardVM - TopIndexOnActivePage]
				->SetCardVisibilityStatus(ESlateVisibility::Hidden);
		}
	}
	
}

void UListContainerViewModel::OnPlayerHasChangedEventHandler(FString NickName, int OldIndex, EListMode CurrentMode)
{

	DrawActiveScreen();

//	FString TextEnum = UEnum::GetValueAsString(CurrentMode);
//	FString ListModeEnum = UEnum::GetValueAsString(CurrentListMode);
//
//	UE_LOG(LogTemp, Warning, TEXT("enum en evento es: %s y este listado es: %s"), *TextEnum, *ListModeEnum);
//	if (CurrentMode == CurrentListMode)
//	{
//		// Add here some BP event for animation or delay?
//
//		DrawActiveScreen();
//		return;
//	}
//
//
//	for (UEncapsulatePlayerData* Data : ListPlayerData)
//{
//	FString Nick = Data->Nickname.ToString();
//	UE_LOG(LogTemp, Warning, TEXT("Usuarios online: %s"), *Nick);
//}
//
//
//	int32 ListOldIndex = ListPlayerData.IndexOfByPredicate([NickName](const UEncapsulatePlayerData* PlayerData)
//		{
//			return PlayerData->Nickname == NickName;
//		});
//
//
//
//
//	// We need to determine if the player is seeing the screen where the player has changed of state
//	// Otherwise, we just redraw
//	float IndexOnPageNumber = FMath::DivideAndRoundDown(ListOldIndex, NumberCardsperScreen);
//	UE_LOG(LogTemp, Warning, TEXT("el indice calculado del oldindex: %d y esta en la pagina: %f"), ListOldIndex, IndexOnPageNumber);
//
//	if (IndexOnPageNumber == CurrentActivePageValue)
//	{
//		//if that is the case, we need to create a animation or graphical effect on the player and
//		//update the list
//		int IndexCardViewModel = ListOldIndex % NumberCardsperScreen;
//		UE_LOG(LogTemp, Warning, TEXT("El indice calculado para el VM que se tiene que ir es: %d"), IndexCardViewModel);
//		
//		// This is just for Testing
//		FTimerHandle TimerHandler;
//		GetWorld()->GetTimerManager().SetTimer(
//			TimerHandler,
//			[this, IndexCardViewModel]()
//			{
//				ListPlayersCardViewModels[IndexCardViewModel]
//					->SetNameField(FText::FromString(TEXT("Esta card tiene que ser borrada")));
//				DrawActiveScreen();
//			},
//			0.5f,
//			false
//		);
//	}
//	else
//	{
//		DrawActiveScreen();
//	}

	
}