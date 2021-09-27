// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameNPCSaying.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameNPCSaying : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* _SpeechText;
	TArray<FString> _SpeechTexts;
public:
	virtual void NativeConstruct() override;

	void SetSpeechText(const FString& Text);
	void SetSpeechTexts(const TArray<FString>& NewTexts);
};
