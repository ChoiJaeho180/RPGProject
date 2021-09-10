// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "RPGIntroLobbyWidget.generated.h"

class UWidgetSwitcher;
class URPGIntroBaseLayout;
class UWidgetAnimation;
class UImage;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLobbyWidget : public URPGIntroBaseWidget
{
	GENERATED_BODY()
private:

public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
public:
	void OnPreWidgetChange(const EIntroUIWidgetState& NewState, const int& ZOrder);
};
