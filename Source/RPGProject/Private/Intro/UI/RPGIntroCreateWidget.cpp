// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroCreateWidget.h"
#include "Intro/UI/RPGIntroBaseLayout.h"

void URPGIntroCreateWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetLayoutList();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::CREATE_CREATE, FString("WB_CreateCharacter_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}
void URPGIntroCreateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::CREATE_CREATE);
	if (LayoutIndex == -1)
		return;
	_IntroLayoutList[LayoutIndex]->delegateSendWidgetChange.BindUObject(this, &URPGIntroCreateWidget::OnPreWidgetChange);
}

void URPGIntroCreateWidget::OnPreWidgetChange(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	ChangeWidget(NewState, 5);
}
