// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Intro/UI/RPGIntroBaseWidget.h"
#include "RPGIntroMainWidget.generated.h"

class URPGIntroBaseLayout;
class UImage;
class UWidgetAnimation;

UCLASS()
class RPGPROJECT_API URPGIntroMainWidget : public URPGIntroBaseWidget
{
	GENERATED_BODY()
public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
public:
	UFUNCTION()
	void OnPreWidgetChange(const EIntroDerivedWidgetState& NewState, const int& ZOrder);
protected:
};
