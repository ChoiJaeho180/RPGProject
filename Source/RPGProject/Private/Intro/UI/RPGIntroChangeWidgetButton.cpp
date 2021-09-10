// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro/UI/RPGIntroChangeWidgetButton.h"

URPGIntroChangeWidgetButton::URPGIntroChangeWidgetButton()
{
	OnClicked.AddDynamic(this, &URPGIntroChangeWidgetButton::OnClick);
}

void URPGIntroChangeWidgetButton::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClick"));
	delegateUpdateWidgetClick.Broadcast(_UpdateWidgetState);
}
