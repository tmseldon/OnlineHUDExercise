// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListContainerViewModel.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "List Params", meta = (AllowPrivateAccess = "true"))
	int NumberOfCardsOnScreenForList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "List Params", meta = (AllowPrivateAccess = "true"))
	EListMode TypeOfList;
};
