// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameQuestSpeechLayout.h"
#include "Components/Textblock.h"
#include "Components/Button.h"

#define SYLLABLE_UPDATE_INTERVAL 0.07f

void URPGGameQuestSpeechLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (_bFirstInit == true) return;

	_SpeechText = Cast<UTextBlock>(GetWidgetFromName("SpeechText"));
	_NegativeButton = Cast<UButton>(GetWidgetFromName("NegativeButton"));
	_NegativeButton->OnClicked.AddDynamic(this, &URPGGameQuestSpeechLayout::OnClickedNegativeeButton);
	_PositiveButton = Cast<UButton>(GetWidgetFromName("PositiveButton"));
	_PositiveButton->OnClicked.AddDynamic(this, &URPGGameQuestSpeechLayout::OnClickedPositiveButton);

	_bFirstInit = true;
}
void URPGGameQuestSpeechLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_bActiveSpeech == false) return;
	_CurrentTime += InDeltaTime;
	if (SYLLABLE_UPDATE_INTERVAL > _CurrentTime) return;

	if (_QuestInfo.Speech.Len() <= _CurrentSpeechIndex)
	{
		_NegativeButton->SetVisibility(ESlateVisibility::Visible);
		_PositiveButton->SetVisibility(ESlateVisibility::Visible);
		_bActiveSpeech = false;
		return;
	}
	_CurrentSpeech += _QuestInfo.Speech[_CurrentSpeechIndex];
	_SpeechText->SetText(FText::FromString(_CurrentSpeech));
	_CurrentSpeechIndex++;
	_CurrentTime = 0;
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
void URPGGameQuestSpeechLayout::OnClickedNegativeeButton()
{
	FRPGQuestQuickInfo QuestQuickInfo;
	delegateChangeQuestToMainWidget.ExecuteIfBound(false, QuestQuickInfo);
}
void URPGGameQuestSpeechLayout::SetQuestInfo(const FRPGQuestInfo& QuestInfo)
{
	_QuestInfo = QuestInfo;
	_CurrentSpeech = "";
	_CurrentSpeechIndex = 0;
	_CurrentTime = 0;
	_bActiveSpeech = true;
	_SpeechText->SetText(FText());
	_NegativeButton->SetVisibility(ESlateVisibility::Hidden);
	_PositiveButton->SetVisibility(ESlateVisibility::Hidden);
}
