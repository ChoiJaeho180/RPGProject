// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/Button.h"
#include "RPGIntroChooseJobButton.generated.h"

DECLARE_DELEGATE(FActiveInputCharacterInfoDelegate);

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroChooseJobButton : public UButton
{
	GENERATED_BODY()
private:
	ECommonJob _KindOfJob;
public:
	URPGIntroChooseJobButton();

	FActiveInputCharacterInfoDelegate delegateActiveInputCharacterInfo;
	UFUNCTION()
	void OnClick();
public:
	FORCEINLINE void SetJob(ECommonJob NewJob) { _KindOfJob = NewJob; }
};
