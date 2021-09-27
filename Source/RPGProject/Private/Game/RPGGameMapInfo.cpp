// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameMapInfo.h"
#include "Game/RPGGameNPCShop.h"
#include "Game/RPGGameNPCQuest.h"

void URPGGameMapInfo::AddNewNPC(ARPGGameNPCQuest* NewNPC)
{
	_QuestNPCs.Add(NewNPC);
}

void URPGGameMapInfo::AddNewNPC(ARPGGameNPCShop* NewNPC)
{
	_ShopNPCs.Add(NewNPC);
}

void URPGGameMapInfo::SetHiddenGame(bool bHide)
{
	for (int i = 0; i < _QuestNPCs.Num(); i++)
	{
		_QuestNPCs[i]->SetActorHiddenInGame(bHide);
	}
	for (int i = 0; i < _ShopNPCs.Num(); i++)
	{
		_ShopNPCs[i]->SetActorHiddenInGame(bHide);
	}
}
