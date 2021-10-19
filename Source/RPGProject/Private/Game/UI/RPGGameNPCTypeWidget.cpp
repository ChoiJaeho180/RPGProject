// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameNPCTypeWidget.h"
#include "Components/TextBlock.h"

void URPGGameNPCTypeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_NPCTypeText = Cast<UTextBlock>(GetWidgetFromName("NPCNameText"));
}

void URPGGameNPCTypeWidget::SetTypeText(const FString& Text)
{
	if (_NPCTypeText != nullptr)
		_NPCTypeText->Text = FText::FromString(Text);
}
