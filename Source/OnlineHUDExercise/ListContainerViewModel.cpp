// Fill out your copyright notice in the Description page of Project Settings.


#include "ListContainerViewModel.h"

void UListContainerViewModel::SetPlayerCard(UUserWidget* CardWidget)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(PlayerCard, CardWidget))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PlayerCard);
    }
}


UUserWidget* UListContainerViewModel::GetPlayerCard() const
{
	return PlayerCard;
}