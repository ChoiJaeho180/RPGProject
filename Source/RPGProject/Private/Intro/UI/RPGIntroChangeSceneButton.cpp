// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro/UI/RPGIntroChangeSceneButton.h"

URPGIntroChangeSceneButton::URPGIntroChangeSceneButton()
{
 	OnClicked.AddDynamic(this, &URPGIntroChangeSceneButton::OnClick);
}

void URPGIntroChangeSceneButton::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClick"));
	delegateUpdateSceneClick.Broadcast(_UpdateProperty);
}
