// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TooltipViewModel.generated.h"

/**
 * This is the view model that controls and sets everything related to the tooltip
 * that appears on the top of the player cards
 */
UCLASS()
class ONLINEHUDEXERCISE_API UTooltipViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/*
	* Getter and setters for the Bind properties
	*/
	FText GetBioText() const;
	void SetBioText(FText NewText);

	FText GetDateInfo() const;
	void SetDateInfo(FText NewText);

	bool GetTooltipVisibilityStatus() const;
	void SetTooltipVisibilityStatus(bool NewStatus);

	// The initialization method where we get the reference for the Widget Parent of this View Model
	// We need this reference to modify its position on the Viewport
	UFUNCTION(BlueprintCallable)
	void InitializeDependencies(class UTooltipExtended* ParentWidget);

	// This is the main methid where we inject the required data from the Player Card View Model
	// Also, we set the visibility here
	void InjectDataAndTrigger(
		bool bIsShown,
		bool bIsOnline,
		FVector2D SpawnPos, 
		FVector2D SpawnSize, 
		FText ProfileText, 
		FDateTime TimeForTooltip);

protected:

	/*
	* Bind properties
	*/

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	bool TooltipVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText BioText;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText DateInfo;

private:

	/*
	* String constant to builds the final texts on the Tooltip
	*/
	const FString BioPrefix = TEXT("Bio: ");
	const FString MinutesOnlineText = TEXT("Minutes online: ");
	const FString MinutesOfflineText = TEXT("Minutes offline: ");

	// Reference of the parent widget
	class UTooltipExtended* TooltipParentWidget;
};
