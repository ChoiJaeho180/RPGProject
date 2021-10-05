// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGmaeDragBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameTitleBarLayout.generated.h"

class UBorder;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameTitleBarLayout : public URPGGmaeDragBaseLayout
{
	GENERATED_BODY()
private:
	UTextBlock* _TitleText;
	UBorder* _TitleBorder;
public:
	virtual void NativeConstruct() override;
public:
	void SetText(FString NewTitle);
};
