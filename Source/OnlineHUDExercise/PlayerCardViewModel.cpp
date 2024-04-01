// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardViewModel.h"
#include "GameModeExtended.h"
#include "GameModeExtended.h"


FText UPlayerCardViewModel::GetNameField() const
{
    return NameField;
}

FText UPlayerCardViewModel::GetAliasField() const
{
    return AliasField;
}


FText UPlayerCardViewModel::GetOnlineField() const
{
    return OnlineField;
}

UTexture2D* UPlayerCardViewModel::GetProfileAvatar() const
{
    return ProfileAvatar;
}


ESlateVisibility UPlayerCardViewModel::GetCardVisibilityStatus() const
{
    return CardVisibilityStatus;
}


void UPlayerCardViewModel::SetNameField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(NameField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(NameField);
    }
}


void UPlayerCardViewModel::SetAliasField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(AliasField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(AliasField);
    }
}


void UPlayerCardViewModel::SetOnlineField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(OnlineField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(OnlineField);
    }
}

void UPlayerCardViewModel::SetProfileAvatar(UTexture2D* NewAvatar)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(ProfileAvatar, NewAvatar))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ProfileAvatar);
    }
}

void UPlayerCardViewModel::SetCardVisibilityStatus(ESlateVisibility NewStatusList)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(CardVisibilityStatus, NewStatusList))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CardVisibilityStatus);
    }
}


void UPlayerCardViewModel::AddDataIntoCard(UEncapsulatePlayerData* NewData)
{
    SetNameField(FText::FromName(NewData->Name));
    SetAliasField(FText::FromName(NewData->Nickname));
    SetProfileAvatar(NewData->ProfilePic);
}

