// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCardExtended.generated.h"

/*
* This enum have the different states for animating the Player Cards
*/
UENUM(BlueprintType)
enum class EPlayerCardAnim : uint8
{
	Disconnected,
	Online,
	FadeOut,
	FadeIn
};

/**
 * This class extend the view because here we gather some references important for the
 * relationship between Player Card and the List Container
 * Also, we need to extend the view, to be able to implement BlueprintImplementableEvent
 * and make accesible for modifying animations and effects on Blueprint
 */
UCLASS()
class ONLINEHUDEXERCISE_API UPlayerCardExtended : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Reference", meta = (AllowPrivateAccess = "true"))
	UListContainerViewModel* ListContainerParent;

public:

	UFUNCTION(BlueprintCallable)
	void InitDependency(UListContainerViewModel* ParentReference);

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerFXOnPlayerCard(int IndexPlayer, EPlayerCardAnim TypeAnimation);
	
};
