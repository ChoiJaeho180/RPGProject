// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameBagslot.h"
#include "Components/Image.h"
#include "Components/Button.h"

void URPGGameBagslot::NativeConstruct()
{
	Super::NativeConstruct();
	_Button = Cast<UButton>(GetWidgetFromName("IconButton"));
	_Icon = Cast<UImage>(GetWidgetFromName("IconImage"));

	_Button->SetVisibility(ESlateVisibility::Hidden);
	_Icon->SetVisibility(ESlateVisibility::Hidden);
}
