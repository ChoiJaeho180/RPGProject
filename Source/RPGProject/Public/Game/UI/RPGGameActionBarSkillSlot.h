// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameActionBarSkillSlot.generated.h"

class UTextBlock;
class UBorder;
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
public:
	virtual void NativeConstruct() override;
	void SetKeyText(FString InputKey);
};
