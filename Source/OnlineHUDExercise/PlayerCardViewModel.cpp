// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardViewModel.h"
#include "GameModeExtended.h"
#include "TooltipViewModel.h"


FText UPlayerCardViewModel::GetNameField() const
{
    return NameField;
}

FText UPlayerCardViewModel::GetAliasField() const
{
    return AliasField;
}

bool UPlayerCardViewModel::GetOnlineField() const
{
    return OnlineField;
}

FText UPlayerCardViewModel::GetLevelField() const
{
    return LevelField;
}

UTexture2D* UPlayerCardViewModel::GetProfileAvatar() const
{
    return ProfileAvatar;
}

ESlateVisibility UPlayerCardViewModel::GetCardVisibilityStatus() const
{
    return CardVisibilityStatus;
}


FText UPlayerCardViewModel::GetLastSeenField() const
{
    return LastSeenField;
}

bool UPlayerCardViewModel::GetbHasPlayerCardAnyHover() const
{
    return bHasPlayerCardAnyHover;
}

void UPlayerCardViewModel::SetbHasPlayerCardAnyHover(bool NewValue)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(bHasPlayerCardAnyHover, NewValue))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bHasPlayerCardAnyHover);
        if (bHasPlayerCardAnyHover)
        {
            UE_LOG(LogTemp, Warning, TEXT("Fui focuseado"));

            TooltipViewModel->InjectDataAndTrigger(true, BioText);

        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Me quitaron el focuseado"));
            TooltipViewModel->InjectDataAndTrigger(false, BioText);
        }
    }
}



void UPlayerCardViewModel::SetLastSeenField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(LastSeenField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(LastSeenField);
    }
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

void UPlayerCardViewModel::SetOnlineField(bool bNewState)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(OnlineField, bNewState))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(OnlineField);
    }
}

void UPlayerCardViewModel::SetLevelField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(LevelField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(LevelField);
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

void UPlayerCardViewModel::SetTooltipVMReference(class UTooltipViewModel* TooltipVM)
{
    TooltipViewModel = TooltipVM;
}


void UPlayerCardViewModel::AddDataIntoCard(UEncapsulatePlayerData* NewData)
{
    SetAliasField(FText::FromName(NewData->Nickname));
    SetNameField(FText::FromName(NewData->Name));
    SetLevelField(FText::FromString(LevelPrefix + FString::FromInt(NewData->Level)));
    SetOnlineField(NewData->bIsOnline);

    if (NewData->ProfilePic != nullptr)
    {
        SetProfileAvatar(NewData->ProfilePic);
    }

    if (!NewData->bIsOnline)
    {        
        SetLastSeenField(FText::FromString(LastSeenOfflineText + NewData->LastSeen.ToFormattedString(TEXT(" %H:%M:%S %d %b '%y"))));
    }

    BioText = NewData->BioInfo;
}