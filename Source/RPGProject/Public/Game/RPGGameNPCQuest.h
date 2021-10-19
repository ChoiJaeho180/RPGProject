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
public:
	virtual void BeginPlay() override;
	void SetQuestList();
	FRPGQuestInfo GetQuest();
};
