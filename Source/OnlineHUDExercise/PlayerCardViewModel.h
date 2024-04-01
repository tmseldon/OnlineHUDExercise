// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerCardViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UPlayerCardViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility CardVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText NameField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText AliasField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText OnlineField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	UTexture2D* ProfileAvatar;


public:

	void SetNameField(FText NewText);
	void SetAliasField(FText NewText);
	void SetOnlineField(FText NewText);
	void SetProfileAvatar(UTexture2D* NewAvatar);
	void SetCardVisibilityStatus(ESlateVisibility NewStatusList);

	FText GetNameField() const;
	FText GetAliasField() const;
	FText GetOnlineField() const;
	UTexture2D* GetProfileAvatar() const;
	ESlateVisibility GetCardVisibilityStatus() const;

	void AddDataIntoCard(class UEncapsulatePlayerData* NewData);
};
