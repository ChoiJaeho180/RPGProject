// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLoginLayout.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLoginLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UButton* _RegisterButton;
public:
	void NativeConstruct() override;
public:
	UFUNCTION()
	void OnRegisterClicked();
};
