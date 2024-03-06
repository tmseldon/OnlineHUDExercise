// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardViewModel.h"

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
