// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/RPGGameQuestLayout.h"
#include "Game/UI/RPGGameQuestSpeechLayout.h"

void URPGGameQuestLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bFirstInit == true) return;
	_QuestSpeechLayout = Cast<URPGGameQuestSpeechLayout>(GetWidgetFromName("QuestSpeechLayout"));
	_QuestSpeechLayout->delegateChangeQuestToMainWidget.BindUObject(this, &URPGGameQuestLayout::SendQuestToMainWidget);
	_bFirstInit = true;
}

void URPGGameQuestLayout::SetQuestInfo(const FRPGQuestInfo& QuestInfo, EGameQuestNPCState State)
{
	_QuestSpeechLayout->SetQuestInfo(QuestInfo, State);
}

void URPGGameQuestLayout::SendQuestToMainWidget(bool bQuestPositive, FRPGQuestQuickInfo& QuestQuickInfo)
{
	delegateChangeQuestToMainWidget.ExecuteIfBound(bQuestPositive, QuestQuickInfo);
}
