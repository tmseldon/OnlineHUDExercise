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
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	UUserWidget* PlayerCard;

public:

	void SetPlayerCard(UUserWidget* CardWidget);


	UUserWidget* GetPlayerCard() const;
	
};
