// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameStatLayout.h"
#include "Game/UI/RPGGameTitleBarLayout.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataCopy.h"
#include "Components/TextBlock.h"

void URPGGameStatLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_TitleBarLayout = Cast<URPGGameTitleBarLayout>(GetWidgetFromName("StatTitleBar"));
	_TitleBarLayout->SetParentWidget(this);

	_LevelText = Cast<UTextBlock>(GetWidgetFromName("LevelText"));
	_StxText = Cast<UTextBlock>(GetWidgetFromName("StxText"));
	_DexText = Cast<UTextBlock>(GetWidgetFromName("DexText"));
	_LukText = Cast<UTextBlock>(GetWidgetFromName("LukText"));
	_IntText = Cast<UTextBlock>(GetWidgetFromName("IntText"));
	_CharacterStat = MakeShareable(new FCharacterStat);
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	_CheckStatData = GI->GetDataCopyClass();
}

void URPGGameStatLayout::Tick()
{
	auto CharacterStat = _CheckStatData->GetCharacterStat();
	if (_CharacterStat->TimeStamp == CharacterStat->TimeStamp) return;
	_CharacterStat->Stat["LEVEL"] = CharacterStat->Stat["LEVEL"];
	_CharacterStat->Stat["STX"] = CharacterStat->Stat["STX"];
	_CharacterStat->Stat["DEX"] = CharacterStat->Stat["DEX"];
	_CharacterStat->Stat["LUK"] = CharacterStat->Stat["LUK"];
	_CharacterStat->Stat["INT"] = CharacterStat->Stat["INT"];
	_CharacterStat->TimeStamp = CharacterStat->TimeStamp;

	_LevelText->SetText(FText::FromString(FString::FromInt(_CharacterStat->Stat["LEVEL"])));
	_StxText->SetText(FText::FromString(FString::FromInt(_CharacterStat->Stat["STX"])));
	_DexText->SetText(FText::FromString(FString::FromInt(_CharacterStat->Stat["DEX"])));
	_LukText->SetText(FText::FromString(FString::FromInt(_CharacterStat->Stat["LUK"])));
	_IntText->SetText(FText::FromString(FString::FromInt(_CharacterStat->Stat["INT"])));
}
