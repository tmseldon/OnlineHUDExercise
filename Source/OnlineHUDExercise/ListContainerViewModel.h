// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ListContainerViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UListContainerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ListVisibilityStatus;


	// References with the Player Card View Models on the List
	TArray<class UPlayerCardViewModel*> ListPlayersCardViewModels;


public:

	// View Models Player Cards
	UFUNCTION(BlueprintCallable)
	void AddCardPlayerVMToList(UPlayerCardViewModel* NewPlayerCard);


	// Button Title methods
	ESlateVisibility GetListVisibilityStatus() const;
	void SetListVisibilityStatus(ESlateVisibility NewStatusList);

	UFUNCTION(BlueprintCallable)
	void OnTitleButtonPress();
};
