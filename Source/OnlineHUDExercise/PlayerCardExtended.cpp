// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardExtended.h"
#include "ListContainerViewModel.h"


void UPlayerCardExtended::InitDependency(UListContainerViewModel* ParentReference)
{
	UE_LOG(LogTemp, Warning, TEXT("Init PLayer card"));
	if (ParentReference != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCardnotnull"));
		ListContainerParent = ParentReference;
	}
}