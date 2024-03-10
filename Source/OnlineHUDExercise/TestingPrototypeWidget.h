// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestingPrototypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UTestingPrototypeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UListView* ListTest;
	
};
