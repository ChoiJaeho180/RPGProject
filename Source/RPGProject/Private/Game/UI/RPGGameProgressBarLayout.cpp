// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameProgressBarLayout.h"
#include "Game/UI/RPGGameProgressBar.h"

void URPGGameProgressBarLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_ProgressBar = Cast<URPGGameProgressBar>(GetWidgetFromName("Bar"));
}