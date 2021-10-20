// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCQuest.h"
#include "Game/RPGGameGameMode.h"

void ARPGGameNPCQuest::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0, 190.f, 0));
	
}

void ARPGGameNPCQuest::SetQuestList()
{
	_HandsQuestList = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode())->GetNPCNameToQuestInfo(_Name);
}

FRPGQuestInfo ARPGGameNPCQuest::GetQuest()
{
	int MinLevel = 100000;
	int MinLevelIndex = -1;
	for (int i = 0; i < _HandsQuestList.Num(); i++)
	{
		if (_HandsQuestList[i].MinLevel < MinLevel)
		{
			MinLevel = _HandsQuestList[i].MinLevel;
			MinLevelIndex = i;
		}
	}
	if (MinLevelIndex == -1) return FRPGQuestInfo();
	else return _HandsQuestList[MinLevelIndex];
}

EGameQuestNPCState ARPGGameNPCQuest::GetQuestNPCState()
{
	return _QuestState;
}

