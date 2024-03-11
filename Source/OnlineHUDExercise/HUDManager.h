// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEHUDEXERCISE_API AHUDManager : public AHUD
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	int NumberPlayerCardVMOnPool = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OnlineScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerCardWidget;

	// Reference for the Player Controller
	APlayerController* CharacterController;

	// Pool of PlayerCard sidgets that we will use for each player
	TArray<class UUserWidget*> ListSpawnedPlayerCardsWidgets;

	// Method to create the Object Pool of Player Card View Models
	void CreatePlayerCardPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
