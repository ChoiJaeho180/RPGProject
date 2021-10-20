// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameItemStruct.h"
#include "GameFramework/Actor.h"
#include "RPGGameDataCopy.generated.h"

class ARPGGamePlayerState;
class ARPGGameBaseEffect;
class ARPGGameCharacter;
UCLASS()
class RPGPROJECT_API ARPGGameDataCopy : public AActor
{
	GENERATED_BODY()
private:
	ARPGGamePlayerState* _CheckStat;
	ARPGGameCharacter* _Character;
private:
	TSharedPtr<FCharacterStat> _CharacterStat;
	TArray<TSharedPtr<FRPGItemInfo>> _CharacterItemInfo;
	TSharedPtr<FMoney> _CharacterMoney;
	
	TArray<TSharedPtr<FGameSkillDataCopyInfo>> _CharacterSkillInfo;
	FRPGQuestQuickInfo _QuestQuickInfo;
	float _DeltaTime;
	bool _bInitFirstItem = false;
	TArray<int> _AddExpLog;
	TArray<int> _AddGoldLog;
	FString _UpdateMapName;
public:	
	// Sets default values for this actor's properties
	ARPGGameDataCopy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CheckQuest();
	void CheckCharacterStat();
	void CheckCharacterItems();
	void CheckAddLog();
	void CehckkCharacterMoney();
	void CheckCharacterSkillCoolDown();
	bool FindSkill(const FName& SkillName);
	TSharedPtr<FGameSkillDataCopyInfo> FindCopySkillInfo(const FName& SkillName);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE FRPGQuestQuickInfo GetQuestQuickInfo() { return _QuestQuickInfo; }
	FORCEINLINE void SetUpdateMapName(const FString& MapName) { _UpdateMapName = MapName; }
	FORCEINLINE FString GetUpdateMapName() { return _UpdateMapName; }
	FORCEINLINE TArray<int> GetAddExpLog() { return _AddExpLog; }
	FORCEINLINE void RemoveAddExpLog() { _AddExpLog.Empty(); }
	FORCEINLINE TArray<int> GetAddGoldLog() { return _AddGoldLog; }
	FORCEINLINE void RemoveAddGoldLog() { _AddGoldLog.Empty(); }
	FORCEINLINE TSharedPtr<FMoney> GetCharacterMoney() { return _CharacterMoney; }
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
	FORCEINLINE TArray<TSharedPtr<FRPGItemInfo>> GetCharacterItemsInfo() { return _CharacterItemInfo; }
	FORCEINLINE TArray<TSharedPtr<FGameSkillDataCopyInfo>> GetSkillCoolDownInfo() { return _CharacterSkillInfo; }
	FORCEINLINE bool GetbInitFirstItem() { return _bInitFirstItem; }
};
