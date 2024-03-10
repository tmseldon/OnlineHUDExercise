// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingPrototypeWidget.h"
#include "GameModeExtended.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"

void UTestingPrototypeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto GameModeReference = UGameplayStatics::GetGameMode(this);
	AGameModeExtended* GameExtended = Cast<AGameModeExtended>(GameModeReference);

	if (GameExtended)
	{
		TArray<UEncapsulateData*> ItemsList = GameExtended->DataTestEncapsulated;
		ListTest->SetListItems(ItemsList);
	}

}