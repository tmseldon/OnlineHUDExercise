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
	int NumberPlayerCardVMOnPool = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OnlineScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ListContainerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerCardWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online Screen Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ToastMessageWidget;


	// Reference for the Player Controller
	APlayerController* CharacterController;

	// Reference for the Game Mode Extended 
	class AGameModeExtended* GameModeExtendedService;

	class UToastMessageViewModel* NewToastVM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Card Components", meta = (AllowPrivateAccess = "true"))
	// Pool of PlayerCard sidgets that we will use for each player
	TArray<class UUserWidget*> ListSpawnedPlayerCardsWidgets;

	// Method to create the Object Pool of Player Card View Models
	void CreatePlayerCardPool();

	void OnChangeData(FString NamePlayer, bool bOnlineStatus, int Level);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceivingPlayerData(FName NamePlayer, bool bOnlineStatus, int Level);

public:

	UFUNCTION(BlueprintCallable)
	void SetToastVMReference(UToastMessageViewModel* ReferenceVM);

};
