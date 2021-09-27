// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameMapInfo.generated.h"

class ARPGGameNPC;
class ARPGGameNPCShop;
class ARPGGameNPCQuest;
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

public:
	void AddNewNPC(ARPGGameNPCQuest* NewNPC);
	void AddNewNPC(ARPGGameNPCShop* NewNPC);
	void SetHiddenGame(bool bHide);
public:
	FORCEINLINE void SetMapName(const FString& MapName) { _MapName = MapName; }
	FORCEINLINE FString GetMapName() { return _MapName; }
};
