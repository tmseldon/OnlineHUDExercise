// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ToastMessageViewModel.generated.h"

/**
 * This is the view model that controls everything shown on the toast message
 */
UCLASS()
class ONLINEHUDEXERCISE_API UToastMessageViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:

	// Init method to gather the required dependencies
	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(AHUDManager* HUDReference);

	// This method is the one that changes the visibility on the toast message
	UFUNCTION(BlueprintCallable)
	void TriggerToastMessage(ESlateVisibility ToastVisibility, class UEncapsulatePlayerData* PlayerData);

	// BlueprintEvent for continuing FX or animation
	// NOTE: this is for testing, it seems that because this class is not the parent one, we cannot call BlueprintImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void OnToastAppear(bool bIsAppearing);


protected:

	/*
	* Bind Properties
	*/

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	ESlateVisibility ToastVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText NameField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText AliasField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	UTexture2D* ProfileAvatar;

	/*
	* Setter and Getters for the bind properties
	*/

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

	// We listen the changes from the HUD Manager related to online players connecting
	UFUNCTION()
	void OnPlayerOnlineEventHandler(FString NickName, class UEncapsulatePlayerData* PlayerData, EListMode CurrentMode);
};
