// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroTitleLayout.generated.h"

class UWidgetAnimation;
class UButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroTitleLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UButton* _StartGameButton;
public:
	void NativeConstruct() override;
public:
	void PlayAnimations();
	UFUNCTION()
	void OnStartClicked();
};
