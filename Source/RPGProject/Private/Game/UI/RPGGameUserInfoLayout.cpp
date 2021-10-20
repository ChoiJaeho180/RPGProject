// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUserInfoLayout.h"
#include "Game/UI/RPGGameProgressBarLayout.h"
#include "Components/ProgressBar.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/UI/RPGGameSpecialBar.h"
#include "Game/UI/RPGGameGetInfoLayout.h"
#include "Game/UI/RPGGameNoticeLayout.h"

void URPGGameUserInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_CharacterStat == nullptr)
	{
		_CharacterStat = MakeShareable(new FCharacterStat);
	}
	_SpecialBar = Cast<URPGGameSpecialBar>(GetWidgetFromName("SpecialBar"));
	_HPBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("HPBar"));
	_MPBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("MPBar"));
	_ExpBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("ExpBar"));
	_GetInfoLayout = Cast<URPGGameGetInfoLayout>(GetWidgetFromName("GetInfoLayout"));
	_NoticeLayout = Cast<URPGGameNoticeLayout>(GetWidgetFromName("NoticeLayout"));
	
	InteractionDeltaTime = 0;
	SetGameDataCopy();
}

void URPGGameUserInfoLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	InteractionDeltaTime += InDeltaTime;
	if (InteractionDeltaTime < STARNDARD_TIME)
		return;
	
	_GetInfoLayout->UpdateFadeText();

	TArray<int> ExpLog = GameDataCopy->GetAddExpLog();
	TArray<int> GoldLog = GameDataCopy->GetAddGoldLog();
	int Num = ExpLog.Num() >= GoldLog.Num() ? GoldLog.Num() : ExpLog.Num();
	for (int i = 0; i < Num; i++)
	{
		_GetInfoLayout->SetGetInfoText(ExpLog[i], false);
		_GetInfoLayout->SetGetInfoText(GoldLog[i], true);
	}
	if(ExpLog.Num() != 0 ) GameDataCopy->RemoveAddExpLog();
	if(GoldLog.Num() != 0) GameDataCopy->RemoveAddGoldLog();

	InteractionDeltaTime = 0.f;
	
	if (_NoticeMap != GameDataCopy->GetUpdateMapName())
	{
		_NoticeMap = GameDataCopy->GetUpdateMapName();
		FString Text = _NoticeMap == "Game_Village" ? L"암벽 마을" : L"모래 사막";
		_NoticeLayout->SetNoticeText(FText::FromString(Text));
		_NoticeLayout->PlayNoticeAnimation();
	}

	TSharedPtr<FCharacterStat> CheckStat = GameDataCopy->GetCharacterStat();
	if (CheckStat->TimeStamp == _CharacterStat->TimeStamp)
		return;
	
	//레벨업 체크 할 곳
	if (_CharacterStat->Stat["LEVEL"] < CheckStat->Stat["LEVEL"])
	{
		_NoticeLayout->SetNoticeText(FText::FromString("Level UP!"));
		_NoticeLayout->PlayNoticeAnimation();
		UE_LOG(LogTemp, Warning, TEXT("LEVEL"));
	}

	_CharacterStat->SetInfo(CheckStat);
	UpdateProperty();
}

void URPGGameUserInfoLayout::SetGameDataCopy()
{
	if (GameDataCopy != nullptr)
		return;

	GameDataCopy = Cast<URPGCommonGameInstance>(GetGameInstance())->GetDataCopyClass();
}

void URPGGameUserInfoLayout::UpdateProperty()
{
	float NewSpecialPercent = (float)_CharacterStat->Stat["SPECIALSTATE"] * 0.01f;
	_SpecialBar->SetSpecialBarPercent(NewSpecialPercent, _CharacterStat->Stat["SPECIALSTATE"]);

	float NewHPPercent = (float)_CharacterStat->Stat["HP"] / _CharacterStat->Stat["MAXHP"];
	_HPBar->UpdateProgressBar(NewHPPercent, _CharacterStat->Stat["HP"], _CharacterStat->Stat["MAXHP"], false);

	float NewMPPercent = (float)_CharacterStat->Stat["MP"] / _CharacterStat->Stat["MAXMP"];
	_MPBar->UpdateProgressBar(NewMPPercent, _CharacterStat->Stat["MP"], _CharacterStat->Stat["MAXMP"], false);

	float NewExpPercent = (float)_CharacterStat->Stat["EXP"] / _CharacterStat->Stat["MAXEXP"];
	_ExpBar->UpdateProgressBar(NewExpPercent, _CharacterStat->Stat["EXP"], _CharacterStat->Stat["MAXEXP"], true);
}


