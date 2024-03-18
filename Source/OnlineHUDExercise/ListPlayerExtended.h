// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListPlayerExtended.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UListPlayerExtended : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ListContainer;


public:

	void InitializeList(TArray<UUserWidget*> PlayerCardsToList);
	
};
