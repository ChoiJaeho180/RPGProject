// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGCommonBaseEffect.generated.h"

DECLARE_DELEGATE(FAttachWidgetDelegate);

class UWidgetAnimation;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonBaseEffect : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	FWidgetAnimationDynamicEvent delegateEndedEffect;
protected:
	UWidgetAnimation* GetAnimation(const FString& AnimName);
public:
	FAttachWidgetDelegate delegateAttachWidget;
public:
	virtual void PlayAnim() {};
};
