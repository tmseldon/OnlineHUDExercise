// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TooltipViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UTooltipViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	FText GetBioText() const;
	void SetBioText(FText NewText);

	FText GetDateInfo() const;
	void SetDateInfo(FText NewText);

	bool GetTooltipVisibilityStatus() const;
	void SetTooltipVisibilityStatus(bool NewStatus);

	void InjectDataAndTrigger(
		bool bIsShown,
		bool bIsOnline,
		FVector2D SpawnPos, 
		FVector2D SpawnSize, 
		FText ProfileText, 
		FDateTime TimeForTooltip);

	UFUNCTION(BlueprintCallable)
	void InitializeDependencies(class UTooltipExtended* ParentWidget);

protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	bool TooltipVisibilityStatus;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText BioText;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText DateInfo;

private:

	const FString BioPrefix = TEXT("Bio: ");
	const FString MinutesOnlineText = TEXT("Minutes online: ");
	const FString MinutesOfflineText = TEXT("Minutes offline: ");

	class UTooltipExtended* TooltipParentWidget;
	
};
