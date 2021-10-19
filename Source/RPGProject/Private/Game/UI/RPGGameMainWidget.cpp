// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "Blueprint/WidgetTree.h"
#include "Game/UI/RPGGameSpecificWidgetJudge.h"
#include "Game/UI/RPGGameQuestLayout.h"
#define WB_IDENTIFIER "WB"


void URPGGameMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bFirstInit == true) return;

	TMap<EGameMainUIType, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EGameMainUIType::QUEST_LAYOUT, FString("WB_QUEST_LAYOUT"));
	WidgetStatToIdentifyMap.Add(EGameMainUIType::USER_LAYOUT, FString("WB_USER_LAYOUT"));
	_RPGGameSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
	int ResultIndex = _RPGGameSpecificWidgetJudge.GetUpdateWidgetIndex(_GameLayoutList, EGameMainUIType::QUEST_LAYOUT);
	if (ResultIndex == -1) return;
	Cast<IRPGGameSetQuestUIInfo>(_GameLayoutList[ResultIndex])->delegateChangeQuestToMainWidget.BindUObject(this, &URPGGameMainWidget::ChangeMainWidget);
	_bFirstInit = true;
}

void URPGGameMainWidget::SetLayoutList()
{
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);
	for (int i = 0; i < AllWidgets.Num(); i++)
	{
		FString CurrentWidgetName = AllWidgets[i]->GetName();
		if (CurrentWidgetName.Contains(WB_IDENTIFIER) == false)
			continue;

		auto NewLayout = Cast<URPGGameBaseLayout>(AllWidgets[i]);
		if (NewLayout == nullptr)
			continue;

		_GameLayoutList.AddUnique(NewLayout);
	}
	
}

void URPGGameMainWidget::SetQuestInfo(FRPGQuestInfo QuestInfo)
{
	int ResultIndex = _RPGGameSpecificWidgetJudge.GetUpdateWidgetIndex(_GameLayoutList, EGameMainUIType::QUEST_LAYOUT);
	if (ResultIndex == -1) return; 
	Cast<IRPGGameSetQuestUIInfo>(_GameLayoutList[ResultIndex])->SetQuestInfo(QuestInfo);
	//->
}

void URPGGameMainWidget::ChangeMainWidget(bool bQuestPositive)
{
	if (bQuestPositive == true)
	{

	}
	ChangeLayout(EGameMainUIType::USER_LAYOUT);
}

URPGGameBaseLayout* URPGGameMainWidget::GetUserLayout()
{
	int ResultIndex = _RPGGameSpecificWidgetJudge.GetUpdateWidgetIndex(_GameLayoutList, EGameMainUIType::USER_LAYOUT);
	return _GameLayoutList[ResultIndex];
}

void URPGGameMainWidget::ChangeLayout(const EGameMainUIType& NewState, const int& ZOrder)
{
	int ResultIndex = _RPGGameSpecificWidgetJudge.GetUpdateWidgetIndex(_GameLayoutList, NewState);
	if (ResultIndex == -1)
		return;
	MainSwicher->SetActiveWidget(_GameLayoutList[ResultIndex]);
}
