// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TooltipViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UTooltipViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility TooltipVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText BioText;

public:

	FText GetBioText() const;
	void SetBioText(FText NewText);

	ESlateVisibility GetTooltipVisibilityStatus() const;
	void SetTooltipVisibilityStatus(ESlateVisibility NewStatus);

	void InjectDataAndTrigger(bool bIsShown, FText ProfileText);
	
};
