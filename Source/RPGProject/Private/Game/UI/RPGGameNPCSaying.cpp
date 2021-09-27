// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameNPCSaying.h"
#include "Components/TextBlock.h"

void URPGGameNPCSaying::NativeConstruct()
{
	Super::NativeConstruct();

	_SpeechText = Cast<UTextBlock>(GetWidgetFromName("SpeechText"));
}

void URPGGameNPCSaying::SetSpeechText(const FString& Text)
{
	if(_SpeechText != nullptr)
		_SpeechText->Text = FText::FromString(Text);
}

void URPGGameNPCSaying::SetSpeechTexts(const TArray<FString>& NewTexts)
{
	_SpeechTexts = NewTexts;
	if (_SpeechTexts.Num() == 1)
		SetSpeechText(_SpeechTexts[0]);
}

