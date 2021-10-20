// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameQuestQuickLayout.generated.h"

class URPGGameTitleBarLayout;
class UTextBlock;
class ARPGGameDataCopy;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameQuestQuickLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
	FRPGQuestQuickInfo _QuestInfo;
	UPROPERTY()
	UTextBlock* _RequireText;
	UPROPERTY()
	ARPGGameDataCopy* _CheckQuestData;
public:
	virtual void NativeConstruct() override;
	void Tick();
	void InitQuestInfo();
};
