// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGIntroTitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroTitleWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* _TitleAnimation;
	UPROPERTY()
	class UButton* _StartGameButton;
public:
	virtual void NativeConstruct() override;
public:
	void PlayAnimations();
	UFUNCTION()
	void OnStartClicked();
};
