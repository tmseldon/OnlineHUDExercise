// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastMessageViewModel.h"
#include "GameModeExtended.h"
#include "HUDManager.h"
#include "ListContainerViewModel.h"
#include "Components/SlateWrapperTypes.h"

FText UToastMessageViewModel::GetNameField() const
{
	return NameField;
}

FText UToastMessageViewModel::GetAliasField() const
{
	return AliasField;
}

ESlateVisibility UToastMessageViewModel::GetToastVisibilityStatus() const
{
	return ToastVisibilityStatus;
}

UTexture2D* UToastMessageViewModel::GetProfileAvatar() const
{
	return ProfileAvatar;
}

void UToastMessageViewModel::SetNameField(FText NewText)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(NameField, NewText))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(NameField);
	}
}

void UToastMessageViewModel::SetAliasField(FText NewText)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(AliasField, NewText))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(NameField);
	}
}

void UToastMessageViewModel::SetToastVisibilityStatus(ESlateVisibility NewStatusToast)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(ToastVisibilityStatus, NewStatusToast))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ToastVisibilityStatus);
	}
}

void UToastMessageViewModel::SetProfileAvatar(UTexture2D* NewAvatar)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(ProfileAvatar, NewAvatar))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ProfileAvatar);
	}
}

void UToastMessageViewModel::InitializeViewModel(AHUDManager* HUDReference)
{
	if (HUDReference == nullptr)
	{
		return;
	}

	HudManager = HUDReference;
	HudManager->OnPlayerHasChangedDataEvent.AddDynamic(this, &UToastMessageViewModel::OnPlayerOnlineEventHandler);
	SetToastVisibilityStatus(ESlateVisibility::Hidden);
}

void UToastMessageViewModel::OnPlayerOnlineEventHandler(FString NickName, class UEncapsulatePlayerData* PlayerData, EListMode CurrentMode)
{
	if (CurrentMode == EListMode::Online)
	{
		TriggerToastMessage(ESlateVisibility::Visible, PlayerData);
	}
}

void UToastMessageViewModel::TriggerToastMessage(ESlateVisibility ToastVisibility, class UEncapsulatePlayerData* PlayerData)
{
	SetToastVisibilityStatus(ToastVisibility);

	// On BP we use the On Visbility Event to detect the visible case and add animations/effects + delay
	if (ToastVisibility == ESlateVisibility::Visible)
	{
		SetNameField(FText::FromName(PlayerData->Name));
		SetAliasField(FText::FromName(PlayerData->Nickname));
		SetProfileAvatar(PlayerData->ProfilePic);
	}
}