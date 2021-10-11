// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbyInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"
#include "Common/RPGCommonStringParser.h"

void URPGIntroLobbyInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		URPGIntroLobbySlotInfoLayout* FirstLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_First_CharacterSlot_Layout")));
		FirstLayout->SetScarecrowIndex(0);
		FirstLayout->delegateChooseNewSlot.BindUObject(this, &URPGIntroLobbyInfoLayout::UpdateChooseSlot);
		_CharacterSlotInfo.Add(FirstLayout);
		URPGIntroLobbySlotInfoLayout* SecondLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_Second_CharacterSlot_Layout")));
		SecondLayout->SetScarecrowIndex(1);
		SecondLayout->delegateChooseNewSlot.BindUObject(this, &URPGIntroLobbyInfoLayout::UpdateChooseSlot);
		_CharacterSlotInfo.Add(SecondLayout);
		URPGIntroLobbySlotInfoLayout* ThirdLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_Third_CharacterSlot_Layout")));
		ThirdLayout->SetScarecrowIndex(2);
		ThirdLayout->delegateChooseNewSlot.BindUObject(this, &URPGIntroLobbyInfoLayout::UpdateChooseSlot);
		_CharacterSlotInfo.Add(ThirdLayout);
		_bInit = true;
	}
	SetSlotInfo();
}

void URPGIntroLobbyInfoLayout::UpdateChooseSlot(const int& iScarecrowIndex, const FString& Name)
{
	if (_ChooseSlotInfo != nullptr)
	{
		_ChooseSlotInfo->SetBackgroundColor(false);
	}
	_ChooseSlotInfo = _CharacterSlotInfo[iScarecrowIndex];
	_ChooseSlotInfo->SetBackgroundColor(true);
	SetCharacterName(Name);
	SetScarecrowIndex(iScarecrowIndex);
}


void URPGIntroLobbyInfoLayout::SetSlotInfo()
{
	int JsonCount = 0;
	
	for (int i = 0; i < _CharacterSlotInfo.Num(); i++)
	{
		if (_CharacterSlotInfo[i]->GetActiveState() != false)
			continue;
		if (Info.Num() <= JsonCount)
			break;
		auto CharacterInfo = Info[JsonCount]->AsObject();
		auto LevelValue = RPGCommonStringParser::GetSpecificStat(CharacterInfo->TryGetField(FString("Stat"))->AsString(),"Level");
		if(LevelValue != FString(""))
			_CharacterSlotInfo[i]->SetLevelText(LevelValue);

		auto JobValue = CharacterInfo->TryGetField(FString("Job"));
		if (JobValue != nullptr)
			_CharacterSlotInfo[i]->SetJobText(JobValue->AsString());

		auto CharacterNameValue = CharacterInfo->TryGetField(FString("CharacterName"));
		if (CharacterNameValue != nullptr)
			_CharacterSlotInfo[i]->SetNameText(CharacterNameValue->AsString());

		_CharacterSlotInfo[i]->SetActive(true);
		JsonCount++;
	}
}

void URPGIntroLobbyInfoLayout::SetCharacterName(const FString& NewName)
{
	_CharacterName = NewName;
}

FString URPGIntroLobbyInfoLayout::GetCharacterName()
{
	return _CharacterName;
}

void URPGIntroLobbyInfoLayout::SetScarecrowIndex(const int& NewIndex)
{
	_ScarecrowIndex = NewIndex;
}

int URPGIntroLobbyInfoLayout::GetScarecrowIndex()
{
	return _ScarecrowIndex;
}
