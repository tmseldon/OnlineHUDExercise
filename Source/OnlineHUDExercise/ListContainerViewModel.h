// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ListContainerViewModel.generated.h"

UENUM(BlueprintType)
enum class EListMode : uint8
{
	Online,
	Offline
};

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UListContainerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

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
	TMap<class UPlayerCardViewModel*, class UUserWidget*> MapPlayersCards;

	UPROPERTY()
	TArray<class UEncapsulatePlayerData*> ListPlayerData;

	void UpdatePlayerList();

	UFUNCTION(BlueprintCallable)
	void DrawActiveScreen();

	UFUNCTION()
	void OnPlayerHasChangedEventHandler(FString NickName, class UEncapsulatePlayerData* PlayerData, EListMode CurrentMode);

	//helper method
	int FindIndexPlayerData(FString NickName);
	bool CheckIndexPlayerIsOnScreen(int PLayerIndex)

protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ListVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CurrentActivePageValue;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxPageValue;

	float TopIndexOnActivePage;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(AHUDManager* HUDReference, EListMode Mode, int NumberCards);

	// View Models Player Cards
	UFUNCTION(BlueprintCallable)
	void AddCardPlayerReferencesToList(UPlayerCardViewModel* NewPlayerCardVM, UUserWidget* NewPlayerCardWidget);


	// Bind properties methods for Slider
	float GetCurrentActivePageValue() const;
	void SetCurrentActivePageValue(float NewValue);

	float GetMaxPageValue() const;
	void SetMaxPageValue(float NewValue);


	/*
	/ Button title section
	*/

	// Bind properties methods for Title Button
	ESlateVisibility GetListVisibilityStatus() const;
	void SetListVisibilityStatus(ESlateVisibility NewStatusList);

	// Event for visibility
	UFUNCTION(BlueprintCallable)
	void OnTitleButtonPress();
};
