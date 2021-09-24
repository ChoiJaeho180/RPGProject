// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "../RPGCommonEnumCollection.h"
#include "Common/UI/RPGCommonChangeLevel.h"
#include "Common/UI/RPGCommonBaseEffect.h"
#include "RPGCommonFade.generated.h"

class UImage;
class UWidgetAnumation;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonFade : public URPGCommonBaseEffect, public IRPGCommonChangeLevel
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UImage* _FadeImage;
	UPROPERTY()
	TArray<UWidgetAnimation*> _FadeAnimations;

	ECommonFadeState _FadeState;
public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
public:
	void SetFadeAnimation();
	UFUNCTION()
	void OnEndedFadeInAnim();
public:
	void SetFadeState(ECommonFadeState NewState);
	virtual void PlayAnim() override;
};
