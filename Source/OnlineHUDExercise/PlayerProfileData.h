// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerProfileData.generated.h"

/**
 * This is the structure of the information on the FTableRow
 * It holds the initial information from players
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerData)
	FText BioText;
};
