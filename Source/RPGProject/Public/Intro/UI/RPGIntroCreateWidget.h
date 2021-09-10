// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "RPGIntroCreateWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroCreateWidget : public URPGIntroBaseWidget
{
	GENERATED_BODY()
public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
};
