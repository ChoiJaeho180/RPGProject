// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbyWidget.h"
#include "Components/Image.h"

void URPGIntroLobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::LOBBY_INFO, FString("WB_Lobby_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}

void URPGIntroLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

