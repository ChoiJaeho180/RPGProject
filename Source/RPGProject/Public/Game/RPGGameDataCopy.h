// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
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
	TSharedPtr<FCharacterStat> _CharacterStat;
	TArray<TSharedPtr<FRPGItemInfo>> _CharacterItemInfo;
	TSharedPtr<FMoney> _CharacterMoney;
	ARPGGamePlayerState* _CheckStat;
	ARPGGameCharacter* _Character;
	TArray<TSharedPtr<FGameSkillDataCopyInfo>> _CharacterSkillInfo;
	float _DeltaTime;
	bool _bInitFirstItem = false;
public:	
	// Sets default values for this actor's properties
	ARPGGameDataCopy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CheckCharacterStat();
	void CheckCharacterItems();
	void CehckkCharacterMoney();
	void CheckCharacterSkillCoolDown();
	bool FindSkill(const FName& SkillName);
	TSharedPtr<FGameSkillDataCopyInfo> FindCopySkillInfo(const FName& SkillName);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE TSharedPtr<FMoney> GetCharacterMoney() { return _CharacterMoney; }
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
	FORCEINLINE TArray<TSharedPtr<FRPGItemInfo>> GetCharacterItemsInfo() { return _CharacterItemInfo; }
	FORCEINLINE TArray<TSharedPtr<FGameSkillDataCopyInfo>> GetSkillCoolDownInfo() { return _CharacterSkillInfo; }
	FORCEINLINE bool GetbInitFirstItem() { return _bInitFirstItem; }
};
