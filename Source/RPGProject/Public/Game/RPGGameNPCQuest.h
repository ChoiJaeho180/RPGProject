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
	ARPGGameNPCQuest();
	virtual void BeginPlay() override;
	void SetQuestList(int CharacterLevel);
	FRPGQuestInfo GetQuest();
	EGameQuestNPCState GetCurrentQuestNPCState();
	EGameQuestNPCState UpdateQuestState(FRPGQuestQuickInfo USerQuest);
	void ComplateQuest();
	void SetCurrentQuestNPCState(EGameQuestNPCState New);
	TArray<int> GetComplateQuestIndex();
public:
	FORCEINLINE FRPGQuestInfo GetCurrentQuest() { return _CurrentQuest; }

};
