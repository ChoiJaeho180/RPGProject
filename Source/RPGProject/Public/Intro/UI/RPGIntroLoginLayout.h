// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLoginLayout.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLoginLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGIntroChangeSceneButton* _RegisterButton;
	UPROPERTY()
	URPGIntroChangeSceneButton* _LoginButton;
	UPROPERTY()
	URPGIntroChangeSceneButton* _ExitButton;
	UPROPERTY()
	UEditableTextBox* _UserNameEditBox;
	UPROPERTY()
	UEditableTextBox* _PasswordEditBox;
public:
	void NativeConstruct() override;
public:
	UFUNCTION()
	void OnChangeLayoutClicked(EIntroDerivedWidgetState NewState);
	UFUNCTION()
	void OnChangeWidgetClicked(EIntroDerivedWidgetState NewState);
};
