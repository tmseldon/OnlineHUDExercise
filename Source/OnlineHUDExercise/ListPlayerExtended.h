// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListContainerViewModel.h"
#include "Blueprint/UserWidget.h"
#include "ListPlayerExtended.generated.h"

/**
 * This extension for the List Player View, it is just for getting some parameters at Editor
 * Here we can set the number of cards and type of list (online or offline)
 * 
 * There are some graphical/ui set up on Blueprint graph that depends on this info
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
