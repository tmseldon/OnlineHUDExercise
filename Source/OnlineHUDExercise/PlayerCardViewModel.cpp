// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardViewModel.h"
#include "JsonDataPlayer.h"
//#include "StructUtils.h"
#include "GameModeExtended.h"

FText UPlayerCardViewModel::GetNameField() const
{
    return NameField;
}

void UPlayerCardViewModel::SetNameField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(NameField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(NameField);
    }
}

FText UPlayerCardViewModel::GetAliasField() const
{
    return AliasField;
}

void UPlayerCardViewModel::SetAliasField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(AliasField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(AliasField);
    }
}

FText UPlayerCardViewModel::GetOnlineField() const
{
    return OnlineField;
}

void UPlayerCardViewModel::SetOnlineField(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(OnlineField, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(OnlineField);
    }
}

void UPlayerCardViewModel::TestingMethod()
{
    UE_LOG(LogTemp, Warning, TEXT("Method call from through viewmodel"));
}

void UPlayerCardViewModel::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    UE_LOG(LogTemp, Warning, TEXT("aqui setting the elements on thje list"));

    if (UEncapsulateData* dataCard = Cast<UEncapsulateData>(ListItemObject))
    {
        UE_LOG(LogTemp, Warning, TEXT("Method call from through viewmodel %s, %s"), *dataCard->Nombre, *dataCard->Alias);

        SetNameField(FText::FromString(dataCard->Nombre));
        SetAliasField(FText::FromString(dataCard->Alias));
    }
}