// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PlayerCardViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API UPlayerCardViewModel : public UMVVMViewModelBase, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	FText NameField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	FText AliasField;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	FText OnlineField;

	void SetNameField(FText NewText);
	void SetAliasField(FText NewText);
	void SetOnlineField(FText NewText);

	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:

	FText GetNameField() const;
	FText GetAliasField() const;
	FText GetOnlineField() const;
	
	void TestingMethod();
	
};
