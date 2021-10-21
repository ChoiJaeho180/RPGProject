// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCQuest.h"
#include "Game/RPGGameGameMode.h"
#include "Components/WidgetComponent.h"
#include "Game/Enemy/RPGGameTImer.h"

void ARPGGameNPCQuest::BeginPlay()
{
	Super::BeginPlay();
	_WidgetCompo->SetRelativeLocation(FVector(12, 0, 220));
}

void ARPGGameNPCQuest::SetQuestList()
{
	_HandsQuestList = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode())->GetNPCNameToQuestInfo(_Name);
}

FRPGQuestInfo ARPGGameNPCQuest::GetQuest()
{
	if (GetCurrentQuestNPCState() == EGameQuestNPCState::ING_YET ||
		GetCurrentQuestNPCState() == EGameQuestNPCState::FINISH)
	{
		return FRPGQuestInfo();
	}
	int MinLevel = 100000;
	int MinLevelIndex = -1;
	for (int i = 0; i < _HandsQuestList.Num(); i++)
	{
		if (_HandsQuestList[i].MinLevel < MinLevel &&
			_HandsQuestList[i].bSuccessed == false)
		{
			MinLevel = _HandsQuestList[i].MinLevel;
			MinLevelIndex = i;
		}
	}
	if (MinLevelIndex == -1)
	{
		SetCurrentQuestNPCState(EGameQuestNPCState::FINISH);
		return FRPGQuestInfo();
	}
	SetCurrentQuestNPCState(EGameQuestNPCState::READY);
	_CurrentQuest = _HandsQuestList[MinLevelIndex];
	return _HandsQuestList[MinLevelIndex];
}

EGameQuestNPCState ARPGGameNPCQuest::GetCurrentQuestNPCState()
{
	return _QuestState;
}

EGameQuestNPCState ARPGGameNPCQuest::UpdateQuestState(FRPGQuestQuickInfo USerQuest)
{
	for (auto& Item : USerQuest.Require)
	{
		if (Item.Value != USerQuest.Current[Item.Key])
			return _QuestState;
	}
	SetCurrentQuestNPCState(EGameQuestNPCState::ING_COMPLATE);
	return _QuestState;
}

void ARPGGameNPCQuest::ComplateQuest()
{
	for (int i = 0; i < _HandsQuestList.Num(); i++)
	{
		if (_HandsQuestList[i].QuestNumber == _CurrentQuest.QuestNumber)
		{
			_HandsQuestList[i].bSuccessed = true;
			break;
		}
	}
}

TArray<int> ARPGGameNPCQuest::GetComplateQuestIndex()
{
	TArray<int> Index;
	for (int i = 0; i < _HandsQuestList.Num(); i++)
	{
		if (_HandsQuestList[i].bSuccessed != true) continue;
		Index.Add(_HandsQuestList[i].QuestNumber);
	}
	return Index;
}

