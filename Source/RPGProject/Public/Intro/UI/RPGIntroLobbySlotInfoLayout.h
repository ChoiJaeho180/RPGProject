// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLobbySlotInfoLayout.generated.h"

class URPGIntroChooseCharacterButton;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLobbySlotInfoLayout : public URPGIntroBaseLayout
{
	GENERATED_BODY()
private:
	int _ScarecrowIndex = 0;
	bool _isActive;
	UPROPERTY()
	URPGIntroChooseCharacterButton* _ChooseButton;
	UPROPERTY()
	UImage* _BackgroundImage;
	UPROPERTY()
	UTextBlock* _LevelText;
	UPROPERTY()
	UTextBlock* _JobText;
	UPROPERTY()
	UTextBlock* _NameText;
public:
	void NativeConstruct() override;

	UFUNCTION()
	void OnClick();
	FORCEINLINE void SetScarecrowIndex(int index) { _ScarecrowIndex = index; }
	FORCEINLINE bool GetActiveState() { return _isActive; }
	FORCEINLINE void SetActive(bool bNew) { _isActive = bNew; }
	FORCEINLINE void SetLevelText(FString NewString) { _LevelText->SetText(FText::FromString(FString("Lv. ") + NewString)); }
	FORCEINLINE void SetJobText(FString NewString) { _JobText->SetText(FText::FromString(NewString)); }
	FORCEINLINE void SetNameText(FString NewString) { _NameText->SetText(FText::FromString(NewString)); }
};
