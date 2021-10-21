// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/RPGGameNPC.h"
#include "RPGGameNPCQuest.generated.h"


/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameNPCQuest : public ARPGGameNPC
{
	GENERATED_BODY()
private:
	TArray<FRPGQuestInfo> _HandsQuestList;
	FRPGQuestInfo _CurrentQuest;
	EGameQuestNPCState _QuestState;
public:
	virtual void BeginPlay() override;
	void SetQuestList();
	FRPGQuestInfo GetQuest();
	EGameQuestNPCState GetCurrentQuestNPCState();
	EGameQuestNPCState UpdateQuestState(FRPGQuestQuickInfo USerQuest);
	void ComplateQuest();
	TArray<int> GetComplateQuestIndex();
public:
	FORCEINLINE FRPGQuestInfo GetCurrentQuest() { return _CurrentQuest; }
	FORCEINLINE void SetCurrentQuestNPCState(EGameQuestNPCState New) { _QuestState = New; }
};
