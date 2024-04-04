// Fill out your copyright notice in the Description page of Project Settings.


#include "TooltipViewModel.h"

FText UTooltipViewModel::GetBioText() const 
{
	return BioText;
}

ESlateVisibility UTooltipViewModel::GetTooltipVisibilityStatus() const
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

void UTooltipViewModel::SetTooltipVisibilityStatus(ESlateVisibility NewStatus)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(TooltipVisibilityStatus, NewStatus))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(TooltipVisibilityStatus);
	}
}

void UTooltipViewModel::InjectDataAndTrigger(bool bIsShown, FText ProfileText)
{
	if (bIsShown)
	{
		SetBioText(ProfileText);
	}
	else
	{
		SetBioText(FText::GetEmpty());
	}
}