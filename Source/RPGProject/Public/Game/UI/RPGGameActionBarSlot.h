// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameActionBarSlot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameActionBarSlot : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* _KeyText;
public:
	virtual void NativeConstruct() override;
	void SetKeyText(FString InputKey);
};
