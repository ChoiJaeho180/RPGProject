// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameActionBarSkillSlot.generated.h"

class UTextBlock;
class UBorder;
class UTexture2D;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameActionBarSkillSlot : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UTextBlock* _KeyText;
	UPROPERTY()
	UBorder* _IconBorder;
	UPROPERTY()
	UBorder* _CooldownBorder;
	UPROPERTY()
	UMaterialInstanceDynamic* _CooldownMaterial;
	TSharedPtr<FGameSkillDataCopyInfo> _SkillCoolDownInfo;
	
public:
	virtual void NativeConstruct() override;
	void SetKeyText(FString InputKey);
	void SetIcon(UTexture2D* icon);
	void Update(const TSharedPtr<FGameSkillDataCopyInfo>& Info);
	void UpdateCoolDownUI(float NewRatio);
	FString GetKeyText();
};
