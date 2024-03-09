// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDController.h"
#include "PlayerCardViewModel.h"
//#include "MVVMSubsystem.h"
#include "Blueprint/UserWidget.h"

void AHUDController::BeginPlay()
{
	Super::BeginPlay();

	//Init

	CharacterController = this->GetOwningPlayerController();

	if (OnlineScreenWidget == nullptr || PlayerCardWidget == nullptr)
	{
		UE_LOG(LogTemp, 
			Warning, 
			TEXT("Something went bad at init on HUDController; OnlineScreenWidget: %s, PlayerCardWidget: %s"),
			OnlineScreenWidget == nullptr ? TEXT("NULL") : TEXT("INIT"),
			PlayerCardWidget == nullptr ? TEXT("NULL") : TEXT("INIT")
			);
		return;
	}

	CreatePlayerCardPool();
}

void AHUDController::CreatePlayerCardPool()
{
	for (int IndexPlayerCard = 0; IndexPlayerCard < NumberPlayerCardVMOnPool; IndexPlayerCard++)
	{
		UUserWidget* WidgetSpawned = CreateWidget(CharacterController, TSubclassOf<class UUserWidget>(PlayerCardWidget), FName(TEXT("PlayerCard"), IndexPlayerCard));

		if (WidgetSpawned)
		{

			ListSpawnedPlayerCardsWidgets.Add(WidgetSpawned);

				UE_LOG(LogTemp,
			Warning,
			TEXT("Here at creation %s"),
					*WidgetSpawned->GetName()
		);

			//UPlayerCardViewModel* PlayerVM = Cast<class UPlayerCardViewModel>(WidgetSpawned);
			//
			//if (PlayerVM)
			//{
			//	ListSpawnedPlayerCardsVM.Add(PlayerVM);

			//	UE_LOG(LogTemp,
			//		Warning,
			//		TEXT("Here at creation")
			//	);
			//}

			//UE_LOG(LogTemp,Warning, TEXT("Here at creation where VM: %s"),
			//	PlayerVM != nullptr ? TEXT("VM not null") : TEXT("it is null")
			//);

			//PlayerVM->TestingMethod();
			
		}
	}
}
