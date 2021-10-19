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

void URPGGameQuestLayout::SetQuestInfo(const FRPGQuestInfo& QuestInfo)
{
	_QuestSpeechLayout->SetQuestInfo(QuestInfo);
}

void URPGGameQuestLayout::SendQuestToMainWidget(bool bQuestPositive)
{
	delegateChangeQuestToMainWidget.ExecuteIfBound(bQuestPositive);
}
