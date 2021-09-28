// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSpecialBar.h"
#include "Components/Image.h"

void URPGGameSpecialBar::NativeConstruct()
{
	Super::NativeConstruct();
	_SpecialBar = Cast<UImage>(GetWidgetFromName(TEXT("SpecialBar")));

}

void URPGGameSpecialBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}
