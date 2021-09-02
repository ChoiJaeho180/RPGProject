// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "RPGCommonEnumCollection.h"
#include "Common/RPGCommonBaseEffect.h"
#include "RPGCommonFade.generated.h"

class UImage;
class UWidgetAnumation;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonFade : public URPGCommonBaseEffect
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
	FORCEINLINE void SetFadeState(ECommonFadeState NewState) { _FadeState = NewState; }
	virtual void PlayAnim() override;
};
