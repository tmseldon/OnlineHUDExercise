// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"
#include "PlayerCardViewModel.h"
#include "MVVMSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "View/MVVMView.h" 

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	//Init

	CharacterController = this->GetOwningPlayerController();

	if (OnlineScreenWidget == nullptr || PlayerCardWidget == nullptr)
	{
		UE_LOG(LogTemp, 
			Warning, 
			TEXT("Something went bad at init on HUDManager; OnlineScreenWidget: %s, PlayerCardWidget: %s"),
			OnlineScreenWidget == nullptr ? TEXT("NULL") : TEXT("INIT"),
			PlayerCardWidget == nullptr ? TEXT("NULL") : TEXT("INIT")
			);
		return;
	}

	UUserWidget* WidgetSpawned = CreateWidget(CharacterController, TSubclassOf<class UUserWidget>(PlayerCardWidget), FName(TEXT("PlayerCard")));
	if (WidgetSpawned)
	{
		WidgetSpawned->AddToViewport();
	}

	if (UMVVMView* ViewModelTest = UMVVMSubsystem::GetViewFromUserWidget(WidgetSpawned))
	{
		UPlayerCardViewModel* NewVM = NewObject<UPlayerCardViewModel>();
		NewVM->SetNameField(FText::FromString(TEXT("Seteado desde afuera manualemnte")));

		ViewModelTest->SetViewModel(FName(TEXT("PlayerCardViewModel")), NewVM);
	}
	
	
	//CreatePlayerCardPool();
}

void AHUDManager::CreatePlayerCardPool()
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
			//	/*ListSpawnedPlayerCardsVM.Add(PlayerVM);*/

			//	UE_LOG(LogTemp,
			//		Warning,
			//		TEXT("Here at creation")
			//	);

			//	
			//}

			//UE_LOG(LogTemp,Warning, TEXT("Here at creation where VM: %s"),
			//	PlayerVM != nullptr ? TEXT("VM not null") : TEXT("it is null")
			//);

			//
			//PlayerVM->TestingMethod();
		}
	}

	//if (UMVVMView* ViewModelTest = UMVVMSubsystem::GetViewFromUserWidget(ListSpawnedPlayerCardsWidgets[0]))
	//{
	//	UPlayerCardViewModel* NewVM = NewObject<UPlayerCardViewModel>();
	//	NewVM->SetNameField(FText::FromString(TEXT("Seteado desde afuera manualemnte")));

	//	ViewModelTest->SetViewModel(FName(TEXT("PlayerCardViewModel")), NewVM);
	//}


}
