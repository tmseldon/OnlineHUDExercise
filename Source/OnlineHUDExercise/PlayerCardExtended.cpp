// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardExtended.h"
#include "ListContainerViewModel.h"


void UPlayerCardExtended::InitDependency(UListContainerViewModel* ParentReference)
{
	if (ParentReference != nullptr)
	{
		ListContainerParent = ParentReference;
	}
}