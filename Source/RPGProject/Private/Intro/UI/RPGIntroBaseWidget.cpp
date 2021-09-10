// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Blueprint/WidgetTree.h"

#define WB_IDENTIFIER "WB"

void URPGIntroBaseWidget::ChangeLayout(const EIntroDerivedWidgetState& NewState, const int& ZOrder)
{
	int ResultIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, NewState);
	if (ResultIndex == -1)
		return;
	IntroSwicher->SetActiveWidget(_IntroLayoutList[ResultIndex]);
}

void URPGIntroBaseWidget::ChangeWidget(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	delegateChangeUI.ExecuteIfBound(NewState);
}

void URPGIntroBaseWidget::SetLayoutList()
{
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);
	for (int i = 0; i < AllWidgets.Num(); i++)
	{
		FString CurrentWidgetName = AllWidgets[i]->GetName();
		if (CurrentWidgetName.Contains(WB_IDENTIFIER) == false)
			continue;

		auto NewLayout = Cast<URPGIntroBaseLayout>(AllWidgets[i]);
		if (NewLayout == nullptr)
			continue;

		NewLayout->delegateSendLayoutChange.BindUObject(this, &URPGIntroBaseWidget::ChangeLayout);
		NewLayout->delegateSendWidgetChange.BindUObject(this, &URPGIntroBaseWidget::ChangeWidget);
		_IntroLayoutList.AddUnique(NewLayout);
	}
}

UWidgetSwitcher* URPGIntroBaseWidget::GetIntroSwitcher() const
{
	return IntroSwicher;
}


