// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "RPGCommonGameInstance.generated.h"

class ARPGCommonRestManager;
class ARPGGameNPCData;
class ARPGGameDataCopy;
class URPGGameDataTableManager;
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
	UPROPERTY()
	ARPGGameDataCopy* _GameDataCopy;
	UPROPERTY()
	URPGGameDataTableManager* _DataTableManager;
	FString _CurrentCharacterName;
	FString _TempToken;
public:
	URPGCommonGameInstance();
	virtual void Init() override;
	bool PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject);
	void Release();
	void CreateGameNPCData();
	void CreateGameDataCopyClass();

public:
	FORCEINLINE void SetCharacterName(FString NewName) { _CurrentCharacterName = NewName; }
	FORCEINLINE FString GetCharacterName() { return _CurrentCharacterName; }
	FORCEINLINE ARPGGameNPCData* GetGameNPCData() { return _GameNPCData; }
	FORCEINLINE ARPGGameDataCopy* GetDataCopyClass() { return _GameDataCopy; }
	FORCEINLINE URPGGameDataTableManager* GetDataTableManager() { return _DataTableManager; }
public:
	TSubclassOf<ARPGCommonRestManager> RestManagerClass;
	TSubclassOf<ARPGGameNPCData> RPGGameClass;
	TSubclassOf<UUserWidget> RPGSlotClass;
	TSubclassOf<UUserWidget> RPGActionBarSlotClass;
	TSubclassOf<UUserWidget> RPGSellHelperClass;
	TSubclassOf<UUserWidget> RPGBuyHelperClass;
	TSubclassOf<UUserWidget> RPGQuestQuickClass;
	TSubclassOf<ARPGGameDataCopy> GameDataCopyClass;
	TSubclassOf<UUserWidget> ItemToolTipClass;
	USkeletalMesh* CharacterSkeletalMeshObject;
};
