// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameMapInfo.generated.h"

class ARPGGameNPC;
class ARPGGameNPCShop;
class ARPGGameNPCQuest;
class ARPGGamePortal;
class URPGCommonGameInstance;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameMapInfo : public UObject
{
	GENERATED_BODY()
private:
	FString _MapName;
	TArray<ARPGGameNPCShop*> _ShopNPCs;
	TArray<ARPGGameNPCQuest*> _QuestNPCs;
	TArray<ARPGGamePortal*> _Portals;
public:
	URPGGameMapInfo();
	void AddNewNPC(ARPGGameNPCQuest* NewNPC);
	void AddNewNPC(ARPGGameNPCShop* NewNPC);
	void CreatePortal(UWorld* world);
	void SetHiddenGame(bool bHide);
public:
	FORCEINLINE void SetMapName(const FString& MapName) { _MapName = MapName; }
	FORCEINLINE FString GetMapName() { return _MapName; }
public:
	TSubclassOf<ARPGGamePortal> PortalClass;
};
