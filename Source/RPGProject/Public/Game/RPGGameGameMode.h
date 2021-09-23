// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/GameMode.h"
#include "RPGGameGameMode.generated.h"

class URPGGameMapInfo;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<FString ,URPGGameMapInfo*> _MapInfo;
	FString _CurrentMapName;
public:
	ARPGGameGameMode();

	void PostLogin(APlayerController* NewPlayer);
	void Logout(AController* Exiting);
	void ActiveMap(const FString& MapName);
	
public:
	TSubclassOf<URPGGameMapInfo> MapInfoClass;


};
