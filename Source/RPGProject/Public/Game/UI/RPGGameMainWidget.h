// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/UI/RPGGameSpecificWidgetJudge.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameMainWidget.generated.h"

class URPGGameBaseLayout;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameMainWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	bool _bFirstInit;
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainSwicher;
	UPROPERTY()
	TArray<URPGGameBaseLayout*> _GameLayoutList;
	FRPGGameSpecificWidgetJudge _RPGGameSpecificWidgetJudge;

public:
	virtual void NativeConstruct() override;
	void SetLayoutList();
	void SetQuestInfo(FRPGQuestInfo QuestInfo);
	UFUNCTION()
	void ChangeMainWidget(bool bQuestPositive);
public:
	URPGGameBaseLayout* GetUserLayout();
	void ChangeLayout(const EGameMainUIType& NewState, const int& ZOrder = 0);
};
