// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "Blueprint/WidgetTree.h"
#include "Game/UI/RPGGameSpecificWidgetJudge.h"

#define WB_IDENTIFIER "WB"


void URPGGameMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TMap<EGameMainUIType, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EGameMainUIType::QUEST_LAYOUT, FString("WB_QUEST_LAYOUT"));
	WidgetStatToIdentifyMap.Add(EGameMainUIType::USER_LAYOUT, FString("WB_USER_LAYOUT"));
	_RPGGameSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
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

		//NewLayout->delegateSendLayoutChange.BindUObject(this, &URPGIntroBaseWidget::ChangeLayout);
		//NewLayout->delegateSendWidgetChange.BindUObject(this, &URPGIntroBaseWidget::ChangeWidget);
		_GameLayoutList.AddUnique(NewLayout);
	}
}

void URPGGameMainWidget::ChangeLayout(const EGameMainUIType& NewState, const int& ZOrder)
{
	int ResultIndex = _RPGGameSpecificWidgetJudge.GetUpdateWidgetIndex(_GameLayoutList, NewState);
	if (ResultIndex == -1)
		return;
	MainSwicher->SetActiveWidget(_GameLayoutList[ResultIndex]);
}
