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

private:

	const FString LevelPrefix = TEXT("Level ");

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
	FText LevelField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	UTexture2D* ProfileAvatar;


public:

	void SetNameField(FText NewText);
	FText GetNameField() const;

	void SetAliasField(FText NewText);
	FText GetAliasField() const;

	void SetOnlineField(FText NewText);
	FText GetOnlineField() const;

	void SetLevelField(FText NewText);
	FText GetLevelField() const;

	void SetProfileAvatar(UTexture2D* NewAvatar);
	UTexture2D* GetProfileAvatar() const;

	void SetCardVisibilityStatus(ESlateVisibility NewStatusList);
	ESlateVisibility GetCardVisibilityStatus() const;

	void AddDataIntoCard(class UEncapsulatePlayerData* NewData);
};
