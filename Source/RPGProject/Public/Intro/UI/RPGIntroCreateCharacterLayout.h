// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroCreateCharacterLayout.generated.h"

class URPGIntroChooseJobButton;
class URPGIntroInputCharacterInfoLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroCreateCharacterLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGIntroChooseJobButton* _JobButton;
	UPROPERTY()
	URPGIntroInputCharacterInfoLayout* _InputCharacterLayout;
public:
	void NativeConstruct() override;
	void ActiveInputCharacterLayout();
	UFUNCTION()
	void OnChangeWidget(const EIntroUIWidgetState& NewState, const int& ZOrder);
};
