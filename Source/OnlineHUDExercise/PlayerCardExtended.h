// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCardExtended.generated.h"

UENUM(BlueprintType)
enum class EPlayerCardAnim : uint8
{
	Disconnected,
	Online,
	FadeOut,
	FadeIn
};

/**
 * 
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
