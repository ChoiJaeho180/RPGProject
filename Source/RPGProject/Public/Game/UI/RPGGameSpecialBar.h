// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameSpecialBar.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameSpecialBar : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UImage* _SpecialBar;
	UPROPERTY()
	UMaterialInstanceDynamic* _MatInst;

	float _CurrentPercent;
	float _NewPercent;
	float _PercentRatio;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	void SetSpecialBarPercent(float NewPercent);

};
