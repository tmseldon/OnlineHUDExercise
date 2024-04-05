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

bool UPlayerCardViewModel::GetbOnlineField() const
{
    return bOnlineField;
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

FVector2D UPlayerCardViewModel::GetWidgetViewPortPos() const
{
    return WidgetViewPortPos;
}

FVector2D UPlayerCardViewModel::GetWidgetViewPortSize() const
{
    return WidgetViewPortSize;
}

void UPlayerCardViewModel::SetWidgetViewPortSize(FVector2D NewValue)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(WidgetViewPortSize, NewValue))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(WidgetViewPortSize);
    }
}

void UPlayerCardViewModel::SetWidgetViewPortPos(FVector2D NewValue)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(WidgetViewPortPos, NewValue))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(WidgetViewPortPos);
    }
}


void UPlayerCardViewModel::SetbHasPlayerCardAnyHover(bool NewValue)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(bHasPlayerCardAnyHover, NewValue))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bHasPlayerCardAnyHover);

        // If we are hovering the Card Player, we send the data required for the Tooltip View Model
        if (bHasPlayerCardAnyHover)
        {
            TooltipViewModel->InjectDataAndTrigger(
                true, 
                bOnlineField, 
                WidgetViewPortPos, 
                WidgetViewPortSize, 
                BioText, 
                TimeforTooltip);
        }
        else
        {
            TooltipViewModel->InjectDataAndTrigger(
                false, 
                bOnlineField, 
                WidgetViewPortPos, 
                WidgetViewPortSize, 
                BioText, 
                TimeforTooltip);
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

void UPlayerCardViewModel::SetbOnlineField(bool bNewState)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(bOnlineField, bNewState))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bOnlineField);
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
    // We set all the info relevant for the Player Card Widget
    SetAliasField(FText::FromName(NewData->Nickname));
    SetNameField(FText::FromName(NewData->Name));
    SetLevelField(FText::FromString(LevelPrefix + FString::FromInt(NewData->Level)));
    SetbOnlineField(NewData->bIsOnline);

    if (NewData->ProfilePic != nullptr)
    {
        SetProfileAvatar(NewData->ProfilePic);
    }

    // Depending on the online/disconnected status we show some additional information
    // We also asign the values for the information for the tooltip
    if (!NewData->bIsOnline)
    {        
        SetLastSeenField(FText::FromString(LastSeenOfflineText + NewData->LastSeen.ToFormattedString(TEXT(" %H:%M:%S %d %b '%y"))));
        TimeforTooltip = NewData->LastSeen;
    }
    else
    {
        TimeforTooltip = NewData->RecentConnection;
    }

    BioText = NewData->BioInfo;
}