// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUserInfoLayout.h"
#include "Game/UI/RPGGameProgressBarLayout.h"

void URPGGameUserInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_HPBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("HPBar"));
}

void URPGGameUserInfoLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}
