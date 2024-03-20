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

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter="IncreasePlayerCardsCount", Getter)
	int32 PlayerCardsAddedCount;

	TArray<class UPlayerCardViewModel*> ListWidgetsDisplayed;


public:
	
	void IncreasePlayerCardsCount(int32 NotUsedValue);
	int GetPlayerCardsAddedCount() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	class UPlayerCardViewModel* AddNewWidgetPlayerCard() const;

	void InitializeList(TArray<class UPlayerCardViewModel*> NewPlayerCards);


	// Button Title methods
	ESlateVisibility GetListVisibilityStatus() const;
	void SetListVisibilityStatus(ESlateVisibility NewStatusList);

	UFUNCTION(BlueprintCallable)
	void OnTitleButtonPress();
};
