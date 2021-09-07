// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Common/UI/RPGCommonChangeScene.h"
#include "Common/UI/RPGCommonFailedEvent.h"
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLoginLayout.generated.h"

class UCircularThrobber;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLoginLayout : public URPGIntroBaseLayout, public IRPGCommonChangeScene, public IRPGCommonFailedEvent
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
	UPROPERTY()
	UTextBlock* _LoginInfoText;
	UPROPERTY()
	UCircularThrobber* _LoadingCircle;
private:
	const FString _LoginUri = FString("/users/login");
	EIntroDerivedWidgetState _TempChangeWidgetState;
	FTimerHandle _TimerHandle;
public:
	void NativeConstruct() override;
public:
	UFUNCTION()
	void OnChangeLayoutClicked(EIntroDerivedWidgetState NewState);
	UFUNCTION()
	void OnChangeWidgetClicked(EIntroDerivedWidgetState NewState);
	virtual void OnChangeWidget() override;
	virtual void RegistFailedEvent() override;
	virtual void ReceiveEvent() override;
	void OnChangeInitProperty();
};
