// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGIntroBaseWidget.generated.h"

DECLARE_DELEGATE_OneParam(FChangeWidgetDelegate, const EIntroUIWidgetState&);
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FChangeWidgetDelegate delegateChangeUI;
};
