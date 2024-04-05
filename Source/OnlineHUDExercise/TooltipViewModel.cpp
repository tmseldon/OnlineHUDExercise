// Fill out your copyright notice in the Description page of Project Settings.


#include "TooltipViewModel.h"
#include "TooltipExtended.h"
#include "Components/CanvasPanelSlot.h"

FText UTooltipViewModel::GetBioText() const 
{
	return BioText;
}

FText UTooltipViewModel::GetDateInfo() const
{
	return DateInfo;
}

bool UTooltipViewModel::GetTooltipVisibilityStatus() const
{
	return TooltipVisibilityStatus;
}

void UTooltipViewModel::SetBioText(FText NewText)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(BioText, NewText))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(BioText);
	}
}

void UTooltipViewModel::SetDateInfo(FText NewText)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(DateInfo, NewText))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(DateInfo);
	}
}

void UTooltipViewModel::SetTooltipVisibilityStatus(bool NewStatus)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(TooltipVisibilityStatus, NewStatus))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(TooltipVisibilityStatus);
	}
}

void UTooltipViewModel::InitializeDependencies(UTooltipExtended* ParentWidget)
{
	TooltipParentWidget = ParentWidget;
}

void UTooltipViewModel::InjectDataAndTrigger(
	bool bIsShown, 
	bool bIsOnline,
	FVector2D SpawnPos, 
	FVector2D SpawnSize, 
	FText ProfileText, 
	FDateTime TimeForTooltip)
{
	if (bIsShown)
	{
		FString CompleteBioText = BioPrefix + ProfileText.ToString();

		SetTooltipVisibilityStatus(true);
		SetBioText(FText::FromString(CompleteBioText));

		if (TooltipParentWidget != nullptr)
		{
			UCanvasPanelSlot* WidgetSlot = Cast<UCanvasPanelSlot>(TooltipParentWidget->Slot);
			WidgetSlot->SetPosition(SpawnPos + FVector2D(165, 0));
		}

		FTimespan DifferenceMinutes = FDateTime::Now() - TimeForTooltip;
		float Minutes = (float)DifferenceMinutes.GetTotalMinutes();
		Minutes *= 10;
		Minutes = FMath::FloorToInt(Minutes);
		Minutes = Minutes / 10.0;

		if (bIsOnline)
		{
			SetDateInfo(FText::FromString(MinutesOnlineText + FString::SanitizeFloat(Minutes, 2)));
		}
		else
		{
			SetDateInfo(FText::FromString(MinutesOfflineText + FString::SanitizeFloat(Minutes, 2)));
		}
	}
	else
	{
		SetTooltipVisibilityStatus(false);
	}
}