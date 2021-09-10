// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGIntroBaseLayout.generated.h"

DECLARE_DELEGATE_TwoParams(FSendLayoutChangeDelegate, const EIntroDerivedWidgetState&, const int&);
DECLARE_DELEGATE_TwoParams(FSendWidgetChangeDelegate, const EIntroUIWidgetState&, const int&);

class UButton;
class UEditableTextBox;
class URPGIntroChangeSceneButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroBaseLayout : public UUserWidget
{
	GENERATED_BODY()
protected:
	bool _bInit;
public:
	FSendLayoutChangeDelegate delegateSendLayoutChange;
	FSendWidgetChangeDelegate delegateSendWidgetChange;
};
