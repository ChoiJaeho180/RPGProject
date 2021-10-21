// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameQuestSpeechLayout.h"
#include "Components/Textblock.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#define SYLLABLE_UPDATE_INTERVAL 0.07f

void URPGGameQuestSpeechLayout::QuestStateVisibility()
{
	if (_QuestState == EGameQuestNPCState::READY)
	{
		if (_QuestInfo.Speech.Len() <= _CurrentSpeechIndex)
		{
			_NegativeButton->SetVisibility(ESlateVisibility::Visible);
			_PositiveButton->SetVisibility(ESlateVisibility::Visible);
			_bActiveSpeech = false;
			return;
		}
	}
	else
	{
		if (_QuestInfo.Speech.Len() <= _CurrentSpeechIndex)
		{
			_AcceptButton->SetVisibility(ESlateVisibility::Visible);
			_bActiveSpeech = false;
			return;
		}
	}

}

void URPGGameQuestSpeechLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (_bFirstInit == true) return;

	_SpeechText = Cast<UTextBlock>(GetWidgetFromName("SpeechText"));
	_NegativeButton = Cast<UButton>(GetWidgetFromName("NegativeButton"));
	_NegativeButton->OnClicked.AddDynamic(this, &URPGGameQuestSpeechLayout::OnClickedNegativeeButton);
	_PositiveButton = Cast<UButton>(GetWidgetFromName("PositiveButton"));
	_PositiveButton->OnClicked.AddDynamic(this, &URPGGameQuestSpeechLayout::OnClickedPositiveButton);
	_AcceptButton = Cast<UButton>(GetWidgetFromName("AcceptButton"));
	_AcceptButton->OnClicked.AddDynamic(this, &URPGGameQuestSpeechLayout::OnClickedAcceptButton);
	_bFirstInit = true;
}
void URPGGameQuestSpeechLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_bActiveSpeech == false) return;
	_CurrentTime += InDeltaTime;
	if (SYLLABLE_UPDATE_INTERVAL > _CurrentTime) return;

	_CurrentSpeech += _QuestInfo.Speech[_CurrentSpeechIndex];
	_SpeechText->SetText(FText::FromString(_CurrentSpeech));
	_CurrentSpeechIndex++;
	_CurrentTime = 0;

	QuestStateVisibility();
}
void URPGGameQuestSpeechLayout::OnClickedPositiveButton()
{
	FRPGQuestQuickInfo QuestQuickInfo;
	QuestQuickInfo.TimeStamp = 0;
	QuestQuickInfo.QuestNumber = _QuestInfo.QuestNumber;
	QuestQuickInfo.Require = _QuestInfo.Require;
	QuestQuickInfo.Current = QuestQuickInfo.Require;
	for (auto& Item : QuestQuickInfo.Current) Item.Value = 0;

	delegateChangeQuestToMainWidget.ExecuteIfBound(true, QuestQuickInfo);
}
void URPGGameQuestSpeechLayout::OnClickedAcceptButton()
{
	FRPGQuestQuickInfo QuestQuickInfo;
	delegateChangeQuestToMainWidget.ExecuteIfBound(false, QuestQuickInfo);
}
void URPGGameQuestSpeechLayout::OnClickedNegativeeButton()
{
	FRPGQuestQuickInfo QuestQuickInfo;
	delegateChangeQuestToMainWidget.ExecuteIfBound(false, QuestQuickInfo);
}
void URPGGameQuestSpeechLayout::SetQuestInfo(const FRPGQuestInfo& QuestInfo, EGameQuestNPCState State)
{
	_QuestState = State;
	if (_QuestState == EGameQuestNPCState::READY)
	{
		_QuestInfo = QuestInfo;
	}
	else if (_QuestState == EGameQuestNPCState::ING_YET)
	{
		_QuestInfo.Speech = L"빨리 해결해 주실수 없을까요?";
	}
	else if (_QuestState == EGameQuestNPCState::ING_COMPLATE)
	{
		_QuestInfo.Speech = L"정말 감사합니다.";
		_QuestInfo.Speech.Append("\r");
		_QuestInfo.Speech.Append("\r");
		_QuestInfo.Speech.Append(L"보상\r");
		for (auto& item : _QuestInfo.Compensation)
		{
			FString Compoensation = item.Key + " : " + FString::FromInt(item.Value) + "\r";
			_QuestInfo.Speech.Append(Compoensation);
		}
	}
	else if (_QuestState == EGameQuestNPCState::FINISH)
	{
		_QuestInfo.Speech = L"마을을 잘 둘러 보세요. 재미난게 있습니다.";
	}

	_CurrentSpeech = "";
	_CurrentSpeechIndex = 0;
	_CurrentTime = 0;
	_bActiveSpeech = true;
	_SpeechText->SetText(FText());
	_NegativeButton->SetVisibility(ESlateVisibility::Hidden);
	_PositiveButton->SetVisibility(ESlateVisibility::Hidden);
	_AcceptButton->SetVisibility(ESlateVisibility::Hidden);
}
