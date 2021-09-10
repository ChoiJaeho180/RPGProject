// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLobbyInteractionLayout.generated.h"

class URPGIntroChangeSceneButton;
class URPGIntroChangeWidgetButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLobbyInteractionLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGIntroChangeWidgetButton* _BackButton;
	UPROPERTY()
	URPGIntroChangeWidgetButton* _StartButton;
	UPROPERTY()
	URPGIntroChangeWidgetButton* _NewCharacterButton;
	UPROPERTY()
	URPGIntroChangeSceneButton* _ChangeCharacterNameButton;
	UPROPERTY()
	URPGIntroChangeSceneButton* _DestroyCharacterButton;
public:
	void NativeConstruct() override;
	UFUNCTION()
	void OnChangeWidgetClicked(const EIntroUIWidgetState& NewState);
};
