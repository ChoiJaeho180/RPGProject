// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/REST/RPGGameSendRegiterResult.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroRegisterLayout.generated.h"

class UCircularThrobber;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroRegisterLayout : public URPGIntroBaseLayout, public IRPGGameSendRegiterResult
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
	UPROPERTY()
	UCircularThrobber* _LoadingCircle;
public:
	void NativeConstruct() override;

	UFUNCTION()
	void OnChangeLayoutClicked(EIntroDerivedWidgetState NewState);
	UFUNCTION()
	void OnRegisterClicked();
	
	virtual void SetRestResult(const FString& ResultCode);
};
