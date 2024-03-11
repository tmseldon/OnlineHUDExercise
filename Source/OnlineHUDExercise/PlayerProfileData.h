// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerProfileData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerProfileData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FName Nickname;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	UTexture2D* ProfilePic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FDateTime LastSeen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	bool bIsOnline;

};
