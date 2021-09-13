// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Common/UI/RPGCommonChangeScene.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroInputCharacterInfoLayout.generated.h"

class URPGIntroChangeWidgetButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroInputCharacterInfoLayout : public URPGIntroBaseLayout, public IRPGCommonChangeScene
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UEditableTextBox* _UserNameEditBox;
	UPROPERTY()
	URPGIntroChangeWidgetButton* _RegisterButton;
	UPROPERTY()
	URPGIntroChangeWidgetButton* _CancelButton;
private:
	const FString _LoginUri = FString("/users/newcharacter");
public:
	void NativeConstruct() override;
	UFUNCTION()
	void OnChangeWidget();
	UFUNCTION()
	void OnChangeWidgetClicked(const EIntroUIWidgetState& NewState);
	UFUNCTION()
	void OnRequest(const EIntroUIWidgetState& NewState);
};
