// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerCardViewModel.generated.h"

/**
 * This is the View Model that controls and set everything on the Player Card Widget
 * It also serves as parent View Model for the Tooltip View Model
 */
UCLASS()
class ONLINEHUDEXERCISE_API UPlayerCardViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/*
	* Getters and setters for the Bind properties
	*/

	void SetNameField(FText NewText);
	FText GetNameField() const;

	void SetAliasField(FText NewText);
	FText GetAliasField() const;

	void SetbOnlineField(bool bNewState);
	bool GetbOnlineField() const;

	void SetLevelField(FText NewText);
	FText GetLevelField() const;

	void SetProfileAvatar(UTexture2D* NewAvatar);
	UTexture2D* GetProfileAvatar() const;

	void SetCardVisibilityStatus(ESlateVisibility NewStatusList);
	ESlateVisibility GetCardVisibilityStatus() const;

	void SetLastSeenField(FText NewText);
	FText GetLastSeenField() const;

	void SetbHasPlayerCardAnyHover(bool NewValue);
	bool GetbHasPlayerCardAnyHover() const;

	void SetWidgetViewPortPos(FVector2D NewValue);
	FVector2D GetWidgetViewPortPos() const;

	void SetWidgetViewPortSize(FVector2D NewValue);
	FVector2D GetWidgetViewPortSize() const;


	// Method to set the reference for the Tooltip View Model
	void SetTooltipVMReference(class UTooltipViewModel* TooltipVM);

	// Main method to add the information shown on the Player Card Widget
	void AddDataIntoCard(class UEncapsulatePlayerData* NewData);

protected:

	/*
	* Bind properties
	*/

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility CardVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText NameField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText AliasField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	bool bOnlineField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText LevelField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText LastSeenField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	UTexture2D* ProfileAvatar;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	bool bHasPlayerCardAnyHover;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FVector2D WidgetViewPortPos;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FVector2D WidgetViewPortSize;


private:

	/*
	* String const to build some of the texts on the Player Card
	*/
	const FString LevelPrefix = TEXT("Level ");
	const FString LastSeenOfflineText = TEXT("Last seen:");

	// Tooltip View Model reference to inject the data associated to this Player Card
	class UTooltipViewModel* TooltipViewModel;

	// Data that is associated to this Player Card and that we potentially inject to the tooltip
	FText BioText;
	FDateTime TimeforTooltip;
};
