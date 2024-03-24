// Fill out your copyright notice in the Description page of Project Settings.


#include "ListContainerViewModel.h"
#include "PlayerCardViewModel.h"
#include "Components/SlateWrapperTypes.h"


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