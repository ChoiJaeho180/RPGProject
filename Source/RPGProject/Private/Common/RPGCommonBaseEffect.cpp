// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/RPGCommonBaseEffect.h"
#include "Blueprint/WidgetTree.h"

UWidgetAnimation* URPGCommonBaseEffect::GetAnimation(const FString& AnimName)
{
	UWidgetAnimation* SearchAnim = nullptr;
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != AnimName)
			continue;
		SearchAnim = WidgetClass->Animations[i];
		break;
	}
	return SearchAnim;
}