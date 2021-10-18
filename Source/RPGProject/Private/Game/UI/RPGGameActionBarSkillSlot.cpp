// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarSkillSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void URPGGameActionBarSkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	_KeyText = Cast<UTextBlock>(GetWidgetFromName("KeyText"));
	_IconBorder = Cast<UBorder>(GetWidgetFromName("IconBorder"));
	_CooldownBorder = Cast<UBorder>(GetWidgetFromName("CooldownBorder"));
	Visibility = ESlateVisibility::Visible;

}

void URPGGameActionBarSkillSlot::SetKeyText(FString InputKey)
{
	_KeyText->SetText(FText::FromString(InputKey));
}
