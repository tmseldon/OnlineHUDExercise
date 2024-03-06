// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDController.h"
#include "PlayerCardViewModel.h"
#include "Blueprint/UserWidget.h"

void AHUDController::BeginPlay()
{
	Super::BeginPlay();

	//Init

	APlayerController* CharacterController = this->GetOwningPlayerController();

	if (OnlineScreenWidget == nullptr || PlayerCardWidget == nullptr)
	{
		return;
	}

	UUserWidget* WidgetSpawned = CreateWidget(CharacterController, TSubclassOf<class UUserWidget>(PlayerCardWidget), FName(TEXT("PlayerCard")));

	if (WidgetSpawned != nullptr)
	{
		auto PlayerVM = Cast<class UPlayerCardViewModel>(WidgetSpawned);
		PlayerVM->TestingMethod();

	}

}
