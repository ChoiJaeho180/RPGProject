// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroMainWidget.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Blueprint/WidgetTree.h"
#define WB_IDENTIFIER "WB"

void URPGIntroMainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetLayoutList();
}

void URPGIntroMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void URPGIntroMainWidget::SetLayoutList()
{
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);
	for (int i = 0; i < AllWidgets.Num(); i++)
	{
		FString CurrentWidgetName = AllWidgets[i]->GetName();
		if (CurrentWidgetName.Contains(WB_IDENTIFIER) == false)
			continue;

		auto NewLayout = Cast<URPGIntroBaseLayout>(AllWidgets[i]);
		if(NewLayout == nullptr)
			continue;

		NewLayout->delegateChangeUI.BindUObject(this, &URPGIntroMainWidget::ChangeLayout);
		_IntroLayoutList.AddUnique(NewLayout);
	}
}

void URPGIntroMainWidget::ChangeLayout(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	int ResultIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, NewState);
	if (ResultIndex == -1)
		return;

	IntroMainSwicher->SetActiveWidget(_IntroLayoutList[ResultIndex]);
}

