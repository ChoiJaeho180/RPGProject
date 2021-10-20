// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameQuestQuickLayout.h"
#include "Game/UI/RPGGameTitleBarLayout.h"
#include "Components/TextBlock.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataCopy.h"

void URPGGameQuestQuickLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_TitleBarLayout = Cast<URPGGameTitleBarLayout>(GetWidgetFromName("QuestTitleBar"));
	_RequireText = Cast<UTextBlock>(GetWidgetFromName("RequireText"));
	_TitleBarLayout->SetParentWidget(this);
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	_CheckQuestData = GI->GetDataCopyClass();
	InitQuestInfo();
}

void URPGGameQuestQuickLayout::Tick()
{
	FRPGQuestQuickInfo QuestInfo = _CheckQuestData->GetQuestQuickInfo();
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		if(_QuestInfo.TimeStamp == -1 && QuestInfo.TimeStamp != -1) SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if (_QuestInfo.TimeStamp == QuestInfo.TimeStamp) return;
		if (QuestInfo.TimeStamp == -1) SetVisibility(ESlateVisibility::Hidden);
		_QuestInfo.Current = QuestInfo.Current;
		_QuestInfo.QuestNumber = QuestInfo.QuestNumber;
		_QuestInfo.Require = QuestInfo.Require;
		_QuestInfo.TimeStamp = QuestInfo.TimeStamp;

		FString Text;
		for (auto& Item : _QuestInfo.Require)
		{
			Text.Append(Item.Key);
			Text.Append("  :  ");
			int Count = FMath::Clamp(_QuestInfo.Current[Item.Key], 0, Item.Value);
			Text.Append(FString::FromInt(Count) + " / " + FString::FromInt(Item.Value));
			Text.Append("\r");
		}
		_RequireText->SetText(FText::FromString(Text));
	}
	
}

void URPGGameQuestQuickLayout::InitQuestInfo()
{
	_QuestInfo.TimeStamp = -1;
}
