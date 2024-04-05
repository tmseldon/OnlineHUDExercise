// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ListContainerViewModel.generated.h"

/*
* Enum with the different types of Player List depending on
* theirs connection
*/
UENUM(BlueprintType)
enum class EListMode : uint8
{
	Online,
	Offline
};

/**
 * This is the View Model that controls everything related to the Player List:
 * List of Player Cards, Title Button and Slider
 */
UCLASS()
class ONLINEHUDEXERCISE_API UListContainerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/*
	* Methods for initialization and injection of data
	*/

	// We initializae the dependencies of this View Model and references
	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(AHUDManager* HUDReference, EListMode Mode, int NumberCards);

	// We get the pointers for the Player Card View Models and theirs parent Player Card Widget
	// This is relevant to instantiate and communicate the changes to the Player Cards
	UFUNCTION(BlueprintCallable)
	void AddCardPlayerReferencesToList(UPlayerCardViewModel* NewPlayerCardVM, UPlayerCardExtended* NewPlayerCardWidget);

	// This method helps to add the pointer for the Tooltip View Model to each of the PLayer Cards View Models
	// We only use one widget as tooltip, but any Player Card View Model can trigger it
	UFUNCTION(BlueprintCallable)
	void InjectTooltipViewModelToCards(class UTooltipViewModel* TooltipVM);

	// Callback method for when the animation is ended, so we can redraw or execute changes on the list
	UFUNCTION(BlueprintCallable)
	void CallbackAnimation(int IndexPlayer);

	/*
	* Getters and setters related to the Slider
	*/
	float GetCurrentActivePageValue() const;
	void SetCurrentActivePageValue(float NewValue);

	float GetMaxPageValue() const;
	void SetMaxPageValue(float NewValue);

	/*
	* Getter and setter related to the Title Button
	*/
	ESlateVisibility GetListVisibilityStatus() const;
	void SetListVisibilityStatus(ESlateVisibility NewStatusList);

	// Function binded to the Slider's value bind property
	// We determine here if we disable the slider
	UFUNCTION(BlueprintPure, FieldNotify)
	bool CheckSliderEnable() const;

	// Event for visibility of the whole menu when the Title Button is clicked
	UFUNCTION(BlueprintCallable)
	void OnTitleButtonPress();


protected:

	/*
	* Bind properties
	*/
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ListVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CurrentActivePageValue;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxPageValue;

	// This property is imporntant because with this we can determine
	// which section we need to show on the Player List container
	float TopIndexOnActivePage;


private:
	/*
	/ Initialization parameters
	*/

	class AHUDManager* HudManager;
	int NumberCardsperScreen;
	EListMode CurrentListMode;

	// References with the Player Card View Models on the List
	TArray<class UPlayerCardViewModel*> ListPlayersCardViewModels;

	// References with the Player Card Widgets on the List
	TMap<class UPlayerCardViewModel*, class UPlayerCardExtended*> MapPlayersCards;

	// The list with the data for every Player Card in this list
	UPROPERTY()
	TArray<class UEncapsulatePlayerData*> ListPlayerData;

	// Method to update the information hold on ListPlayerData
	// Particularly important if we need to sync the data with the HUD Manager
	void UpdatePlayerList();

	// Method to redraw the information shown on the Player List container
	UFUNCTION(BlueprintCallable)
	void DrawActiveScreen();

	// Event for listening the changes on Player's data and status
	UFUNCTION()
	void OnPlayerHasChangedEventHandler(FString NickName, class UEncapsulatePlayerData* PlayerData, EListMode CurrentMode);

	/*
	* Helper Methods for drawing and determing Player Cards information/View Models
	*/
	bool CheckIndexPlayerIsOnScreen(int PlayerIndex);
	int GetCurrentTopIndex() const;
	int FindIndexPlayerData(FString NickName);
	void SafeRemovePlayerAtIndex(int PlayerIndex);
};
