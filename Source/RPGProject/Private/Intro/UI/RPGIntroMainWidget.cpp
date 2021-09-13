// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroMainWidget.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"

void URPGIntroMainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//SetLayoutList();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_LOGIN, FString("WB_Login_Layout"));
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_TITLE, FString("WB_Title_Layout"));
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_REGISTER, FString("WB_Register_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}

void URPGIntroMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::MAIN_LOGIN);
	if (LayoutIndex == -1)
		return;
	_IntroLayoutList[LayoutIndex]->delegateSendWidgetChange.BindUObject(this, &URPGIntroMainWidget::OnPreWidgetChange);
}

void URPGIntroMainWidget::OnPreWidgetChange(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	ChangeWidget(NewState, 5);
}

