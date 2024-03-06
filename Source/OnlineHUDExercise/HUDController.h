// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDController.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API AHUDController : public AHUD
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OnlineScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerCardWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
