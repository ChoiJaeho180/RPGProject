// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Components/Button.h"
void URPGIntroLoginLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_RegisterButton = Cast<UButton>(GetWidgetFromName(TEXT("RegisterButton")));
	_RegisterButton->OnClicked.AddDynamic(this, &URPGIntroLoginLayout::OnRegisterClicked);
}

void URPGIntroLoginLayout::OnRegisterClicked()
{
	delegateChangeUI.ExecuteIfBound(EIntroUIWidgetState::Title, 0);
}
