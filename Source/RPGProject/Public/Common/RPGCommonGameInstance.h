// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "RPGCommonGameInstance.generated.h"

class ARPGCommonRestManager;
class ARPGGameNPCData;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	ARPGCommonRestManager* _RestManager;
	UPROPERTY()
	ARPGGameNPCData* _GameNPCData;
	FString _CurrentCharacterName;
	FString _TempToken;
public:
	URPGCommonGameInstance();
	virtual void Init() override;
	bool PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject);
	void Release();
	void CreateGameNPCData();
public:
	FORCEINLINE void SetCharacterName(FString NewName) { _CurrentCharacterName = NewName; }
	FORCEINLINE FString GetCharacterName() { return _CurrentCharacterName; }
	FORCEINLINE ARPGGameNPCData* GetGameNPCData() { return _GameNPCData; }
public:
	TSubclassOf<ARPGCommonRestManager> RestManagerClass;
	TSubclassOf<ARPGGameNPCData> RPGGameClass;
	USkeletalMesh* CharacterSkeletalMeshObject;
};
