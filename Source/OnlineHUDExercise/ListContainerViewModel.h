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

	UFUNCTION(BlueprintCallable)
	void DrawActiveScreen();


protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ListVisibilityStatus;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(AHUDManager* HUDReference, EListMode Mode, int NumberCards);

	// View Models Player Cards
	UFUNCTION(BlueprintCallable)
	void AddCardPlayerReferencesToList(UPlayerCardViewModel* NewPlayerCardVM, UUserWidget* NewPlayerCardWidget);


	/*
	/ Button title section
	*/

	// Bind properties methods
	ESlateVisibility GetListVisibilityStatus() const;
	void SetListVisibilityStatus(ESlateVisibility NewStatusList);

	// Event for visibility
	UFUNCTION(BlueprintCallable)
	void OnTitleButtonPress();
};
