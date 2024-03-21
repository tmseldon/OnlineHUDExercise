// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ToastMessageViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UToastMessageViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ToastVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText NameField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText AliasField;

	void SetToastVisibilityStatus(ESlateVisibility NewStatusToast);
	void SetNameField(FText NewText);
	void SetAliasField(FText NewText);

	ESlateVisibility GetToastVisibilityStatus() const;
	FText GetNameField() const;
	FText GetAliasField() const;

public:
	
	UFUNCTION(BlueprintCallable)
	void TriggerToastMessage(ESlateVisibility ToastVisibility, FString NamePlayer = "", FString AliasPlayer = "");
	
};
