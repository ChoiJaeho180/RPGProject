// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/RPGameFadeTextBlock.h"
#include "Components/TextBlock.h"

void URPGameFadeTextBlock::Update()
{
	float Opacity = GetRenderOpacity();
	if (Opacity <= 0.f)
	{
		SetbActive(false);
		return;
	}
	Opacity -= 0.01;
	SetOpacity(Opacity);
}

void URPGameFadeTextBlock::SetOpacity(float Opacity)
{
	SetRenderOpacity(Opacity);
}

FText URPGameFadeTextBlock::GetLogText()
{
	return GetText();
}

void URPGameFadeTextBlock::SetLogText(FText NewText)
{
	SetText(NewText);
}
