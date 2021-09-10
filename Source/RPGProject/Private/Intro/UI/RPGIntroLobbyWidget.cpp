// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbyWidget.h"
#include "Components/Image.h"
#include "Intro/UI/RPGIntroBaseLayout.h"

void URPGIntroLobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetLayoutList();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::LOBBY_INFO, FString("WB_Lobby_Interaction_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}

void URPGIntroLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::LOBBY_INFO);
	if (LayoutIndex == -1)
		return;
	_IntroLayoutList[LayoutIndex]->delegateSendWidgetChange.BindUObject(this, &URPGIntroLobbyWidget::OnPreWidgetChange);
}

void URPGIntroLobbyWidget::OnPreWidgetChange(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	ChangeWidget(NewState, 5);
}
