// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"
#include "GameModeExtended.h"
#include "ListContainerViewModel.h"
#include "ListPlayerExtended.h"
#include "PlayerCardViewModel.h"
#include "MVVMSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "View/MVVMView.h" 

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	//Init

	GameModeExtendedService = Cast<AGameModeExtended>(GetWorld()->GetAuthGameMode());
	if (GameModeExtendedService != nullptr)
	{
		GameModeExtendedService->OnPlayerDataHasChanged.BindUObject(this, &AHUDManager::OnChangeData);
	}

}


void AHUDManager::OnChangeData(FString NamePlayer, bool bOnlineStatus, int Level)
{
	// BluepreintEvent
	OnReceivingPlayerData(FName(*NamePlayer), bOnlineStatus, Level);
}







	//CharacterController = this->GetOwningPlayerController();

	//if (OnlineScreenWidget == nullptr || ListContainerWidget == nullptr || PlayerCardWidget == nullptr)
	//{
	//	UE_LOG(LogTemp, 
	//		Warning, 
	//		TEXT("Something went bad at init on HUDManager; OnlineScreenWidget: %s, ListContainerWidget: %s, PlayerCardWidget: %s"),
	//		OnlineScreenWidget == nullptr ? TEXT("NULL") : TEXT("INIT"),
	//		ListContainerWidget == nullptr ? TEXT("NULL") : TEXT("INIT"),
	//		PlayerCardWidget == nullptr ? TEXT("NULL") : TEXT("INIT")
	//		);
	//	return;
	//}


	//UUserWidget* WidgetSpawned = CreateWidget(CharacterController, TSubclassOf<class UUserWidget>(ListContainerWidget), FName(TEXT("ListContainerWidget")));
	//if (WidgetSpawned)
	//{
	//	WidgetSpawned->AddToViewport();
	//}

	//TArray<UUserWidget*> PlayerCardChildren;
	//TArray<UPlayerCardViewModel*> PlayersViewModel;

	////if (UMVVMView* ViewModelTest = UMVVMSubsystem::GetViewFromUserWidget(WidgetSpawned))
	////{
	//	UE_LOG(LogTemp, Warning, TEXT("aqui despues de pasar el chequeo que la lsita tiene un viewmodel"));
	//	//UListContainerViewModel* NewListVM = NewObject<UListContainerViewModel>();
	//	//ViewModelTest->SetViewModel(FName(TEXT("ListContainerViewModel")), NewListVM);

	//	for (int Index = 0; Index < NumberPlayerCardVMOnPool; ++Index)
	//	{
	//		UUserWidget* PlayerCardWidgetSpawned = 
	//			CreateWidget(CharacterController, 
	//				TSubclassOf<class UUserWidget>(PlayerCardWidget), 
	//				FName(TEXT("PlayerCardWidget"), Index)
	//			);

	//		UE_LOG(LogTemp, Warning, TEXT("aqui creando card widgets children"));


	//		PlayerCardChildren.Add(PlayerCardWidgetSpawned);
	//	}



	//	UListPlayerExtended* ListPlayer = Cast<UListPlayerExtended>(WidgetSpawned);
	//	if (ListPlayer != nullptr)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("tratando de inicializr el lisplayer widget como cast"));
	//		ListPlayer->InitializeList(PlayerCardChildren);
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("No se pudo hacer el casting para init lista"))
	//	}


//		UMVVMView* ViewModelCard;
//		int IndexVM = 0;
//
//		for (UUserWidget* PlayerCardChild : PlayerCardChildren)
//		{
//			ViewModelCard = UMVVMSubsystem::GetViewFromUserWidget(PlayerCardChild);
//			
//			UE_LOG(LogTemp, Warning, TEXT("ViewModel en child es en hud manager: %s y Child es: %s"), *ViewModelCard->GetName(), *PlayerCardChild->GetName());
//			
//			/* Probar este para el caso de que se instnacie de forma automática*/
//			
//			/*TScriptInterface<INotifyFieldValueChanged> VM = ViewModelCard->GetViewModel(FName(TEXT("PlayerCardViewModel")));
//			UE_LOG(LogTemp, Warning, TEXT("ViewModel getViewmodel es %s"), VM == nullptr ? TEXT("vacio") : TEXT("alun nombre"));
//		
//	//
////}*/
//			UPlayerCardViewModel* NewPlayerCardVM = NewObject<UPlayerCardViewModel>(PlayerCardChild, FName(TEXT("PlayerCardViewModel"), IndexVM));
//			ViewModelCard->SetViewModel(FName(TEXT("PlayerCardViewModel"), IndexVM), NewPlayerCardVM);
//			++IndexVM;
//		
//		}

		

	//	if (UMVVMView* ViewModelCard = UMVVMSubsystem::GetViewFromUserWidget(PlayerCardWidgetSpawned))
	//	{


	//		FString Testing = ViewModelCard->GetName();
	//		UE_LOG(LogTemp, Warning, TEXT("aqui csi detectamos qeue le player card tiene view model %s"), *Testing);

	//		UPlayerCardViewModel* NewPlayerCardVM = NewObject<UPlayerCardViewModel>(PlayerCardWidgetSpawned, FName(TEXT("PlayerCardViewModel"), Index));
	//		ViewModelCard->SetViewModel(FName(TEXT("PlayerCardViewModel"), Index), NewPlayerCardVM);
	//		PlayersViewModel.Add(NewPlayerCardVM);
	//	}





	//for (UPlayerCardViewModel* PlayVM : PlayersViewModel)
	//{
	//	PlayVM->SetAliasField(FText::FromString("aqui estoy initi "));
	//}
	//
	
	//CreatePlayerCardPool();
//}

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
