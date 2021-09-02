// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Blueprint/WidgetTree.h"

#define WB_IDENTIFIER "WB"

void URPGIntroBaseWidget::ChangeLayoutAndWidget(const EIntroDerivedWidgetState& NewState, const int& ZOrder)
{
	if (NewState == EIntroDerivedWidgetState::TO_LOBBY)
	{
		delegateChangeUI.ExecuteIfBound(EIntroUIWidgetState::LOBBY);
		return;
	}

	int ResultIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, NewState);
	if (ResultIndex == -1)
		return;

	IntroSwicher->SetActiveWidget(_IntroLayoutList[ResultIndex]);
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

		NewLayout->delegateSendLayoutChange.BindUObject(this, &URPGIntroBaseWidget::ChangeLayoutAndWidget);
		_IntroLayoutList.AddUnique(NewLayout);
	}
}

UWidgetAnimation* URPGIntroBaseWidget::GetAnimation(const FString& AnimName)
{
	UWidgetAnimation* SearchAnim = nullptr;
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != AnimName)
			continue;
		SearchAnim = WidgetClass->Animations[i];
		break;
	}
	return SearchAnim;
}
