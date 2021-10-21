// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCQuest.h"
#include "Game/RPGGameGameMode.h"
#include "Components/WidgetComponent.h"
#include "Game/Enemy/RPGGameTImer.h"
#include "Game/UI/RPGGameNPCSaying.h"

ARPGGameNPCQuest::ARPGGameNPCQuest()
{
	static ConstructorHelpers::FClassFinder<URPGGameNPCSaying> UI_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/NPC/NPC_Quest.NPC_Quest_C'"));
	if (UI_HUD.Succeeded())
	{
		_WidgetCompo->SetWidgetClass(UI_HUD.Class);
		_WidgetCompo->SetDrawSize(FVector2D(220.0f, 30.0f));
	}

}
void ARPGGameNPCQuest::BeginPlay()
{
	Super::BeginPlay();
	_WidgetCompo->SetRelativeLocation(FVector(20.0f, 70.0f, 240.0f));
	SetCurrentQuestNPCState(EGameQuestNPCState::FINISH);
	auto NPCWidget = Cast<URPGGameNPCSaying>(_WidgetCompo->GetUserWidgetObject());
	NPCWidget->NativeConstruct();
}

void ARPGGameNPCQuest::SetQuestList(int CharacterLevel)
{
	_HandsQuestList = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode())->GetNPCNameToQuestInfo(_Name);
	int CompareLevel = 100000;
	for (int i = 0; i < _HandsQuestList.Num(); i++)
	{
		if (_HandsQuestList[i].bSuccessed == false &&
			_HandsQuestList[i].MinLevel <= CharacterLevel &&
			CompareLevel > _HandsQuestList[i].MinLevel)
		{
			CompareLevel = _HandsQuestList[i].MinLevel;
			_CurrentQuest = _HandsQuestList[i];
			SetCurrentQuestNPCState(EGameQuestNPCState::READY);
		}
	}
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

void ARPGGameNPCQuest::SetCurrentQuestNPCState(EGameQuestNPCState New)
{
	 _QuestState = New; 
	 auto NPCWidget = Cast<URPGGameNPCSaying>(_WidgetCompo->GetUserWidgetObject());
	 FString Speech;
	 if (_QuestState == EGameQuestNPCState::READY) Speech = "!";
	 else if (_QuestState == EGameQuestNPCState::ING_YET)Speech = "...";
	 else if (_QuestState == EGameQuestNPCState::ING_COMPLATE)Speech = "?";
	 else Speech = " ";
	 NPCWidget->SetSpeechText(Speech);
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

