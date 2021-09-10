// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro/UI/RPGIntroChooseJobButton.h"

URPGIntroChooseJobButton::URPGIntroChooseJobButton()
{
	OnClicked.AddDynamic(this, &URPGIntroChooseJobButton::OnClick);
}

void URPGIntroChooseJobButton::OnClick()
{
	delegateActiveInputCharacterInfo.ExecuteIfBound();
}
