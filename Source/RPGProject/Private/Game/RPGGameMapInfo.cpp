// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameMapInfo.h"
#include "Game/RPGGameNPCShop.h"
#include "Game/RPGGameNPCQuest.h"
#include "Game/RPGGamePortal.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"

URPGGameMapInfo::URPGGameMapInfo()
{
	PortalClass = ARPGGamePortal::StaticClass();
}

void URPGGameMapInfo::AddNewNPC(ARPGGameNPCQuest* NewNPC)
{
	_QuestNPCs.Add(NewNPC);
}

void URPGGameMapInfo::AddNewNPC(ARPGGameNPCShop* NewNPC)
{
	_ShopNPCs.Add(NewNPC);
}

void URPGGameMapInfo::CreatePortal()
{;
	URPGGameDataTableManager* DTManager = Cast<URPGCommonGameInstance>(_World->GetGameInstance())->GetDataTableManager();
	TArray<FPortalInfo*> PortalInfo = DTManager->GetPortalNameToData(_MapName);
	for (int i = 0; i < PortalInfo.Num(); i++)
	{
		ARPGGamePortal* NewPortal = _World->SpawnActor<ARPGGamePortal>(PortalClass);
		NewPortal->Init(PortalInfo[i]);
		NewPortal->SetActorHiddenInGame(false);
		_Portals.Add(NewPortal);
	}
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
	for (int i = 0; i < _Portals.Num(); i++)
	{
		_Portals[i]->SetActorHiddenInGame(bHide);
	}
}
