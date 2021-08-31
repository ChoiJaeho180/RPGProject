// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroRegisterLayout.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroRegisterLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGIntroChangeSceneButton* _ExitButton;
	UPROPERTY()
	URPGIntroChangeSceneButton* _RegisterButton;
	UPROPERTY()
	UEditableTextBox* _UserNameEditBox;
	UPROPERTY()
	UEditableTextBox* _PasswordEditBox;
	UPROPERTY()
	UEditableTextBox* _CheckPasswordEditBox;
	UPROPERTY()
	UTextBlock* _RegisterInfo;
public:
	void NativeConstruct() override;

	UFUNCTION()
	void OnClicked(EIntroUIWidgetState NewState);
};
