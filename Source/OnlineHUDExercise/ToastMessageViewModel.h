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

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	UTexture2D* ProfileAvatar;

	void SetToastVisibilityStatus(ESlateVisibility NewStatusToast);
	void SetNameField(FText NewText);
	void SetAliasField(FText NewText);
	void SetProfileAvatar(UTexture2D* NewAvatar);

	ESlateVisibility GetToastVisibilityStatus() const;
	FText GetNameField() const;
	FText GetAliasField() const;
	UTexture2D* GetProfileAvatar() const;

private:

	/*
	/ Initialization parameters
	*/
	class AHUDManager* HudManager;

	UFUNCTION()
	void OnPlayerOnlineEventHandler(FString NickName, class UEncapsulatePlayerData* PlayerData, EListMode CurrentMode);

public:
	
	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(AHUDManager* HUDReference);

	UFUNCTION(BlueprintCallable)
	void TriggerToastMessage(ESlateVisibility ToastVisibility, class UEncapsulatePlayerData* PlayerData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnToastAppear(bool bIsAppearing);
	
};
