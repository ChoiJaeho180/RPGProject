// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarSlot.h"
#include "Components/TextBlock.h"

void URPGGameActionBarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	_KeyText = Cast<UTextBlock>(GetWidgetFromName("KeyText"));
}

void URPGGameActionBarSlot::SetKeyText(FString InputKey)
{
	_KeyText->SetText(FText::FromString(InputKey));
}
