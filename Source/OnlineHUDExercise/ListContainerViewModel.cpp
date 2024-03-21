// Fill out your copyright notice in the Description page of Project Settings.


#include "ListContainerViewModel.h"
#include "PlayerCardViewModel.h"
#include "Components/SlateWrapperTypes.h"


int UListContainerViewModel::GetPlayerCardsAddedCount() const
{
	return PlayerCardsAddedCount;
}

void UListContainerViewModel::IncreasePlayerCardsCount(int32 NotUsedValue)
{
	int32 NewCount = PlayerCardsAddedCount + 1;
	UE_MVVM_SET_PROPERTY_VALUE(PlayerCardsAddedCount, NewCount);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(AddNewWidgetPlayerCard);
}

UPlayerCardViewModel* UListContainerViewModel::AddNewWidgetPlayerCard() const
{
	return ListWidgetsDisplayed[PlayerCardsAddedCount];
}

void UListContainerViewModel::InitializeList(TArray<UPlayerCardViewModel*> NewPlayerCards)
{
	if (NewPlayerCards.IsEmpty())
	{
		return;
	}

	for (UPlayerCardViewModel* PlayerCard : NewPlayerCards)
	{

		ListWidgetsDisplayed.Add(PlayerCard);
		IncreasePlayerCardsCount(1);
	}
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