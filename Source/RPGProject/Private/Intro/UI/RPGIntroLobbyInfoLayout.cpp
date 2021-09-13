// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbyInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"

void URPGIntroLobbyInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		URPGIntroLobbySlotInfoLayout* FirstLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_First_CharacterSlot_Layout")));
		FirstLayout->SetScarecrowIndex(0);
		_CharacterSlotInfo.Add(FirstLayout);
		URPGIntroLobbySlotInfoLayout* SecondLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_Second_CharacterSlot_Layout")));
		SecondLayout->SetScarecrowIndex(1);
		_CharacterSlotInfo.Add(SecondLayout);
		URPGIntroLobbySlotInfoLayout* ThirdLayout = Cast<URPGIntroLobbySlotInfoLayout>(GetWidgetFromName(TEXT("WB_Third_CharacterSlot_Layout")));
		ThirdLayout->SetScarecrowIndex(2);
		_CharacterSlotInfo.Add(ThirdLayout);
		_bInit = true;
	}
	SetSlotInfo();
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
		auto LevelValue = CharacterInfo->TryGetField(FString("Level"));
		if(LevelValue != nullptr)
			_CharacterSlotInfo[i]->SetLevelText(LevelValue->AsString());

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
