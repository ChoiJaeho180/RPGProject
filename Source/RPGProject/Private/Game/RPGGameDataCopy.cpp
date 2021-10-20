// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameDataCopy.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"
#include "Game/Skill/RPGGameBaseEffect.h"
#include "Game/RPGGameCharacter.h"

// Sets default values
ARPGGameDataCopy::ARPGGameDataCopy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_CharacterStat = MakeShareable(new FCharacterStat());
	_CharacterMoney = MakeShareable(new FMoney());
}

// Called when the game starts or when spawned
void ARPGGameDataCopy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	_CheckStat = Controller->GetPlayerState<ARPGGamePlayerState>();
	_Character = Cast<ARPGGameCharacter>(Controller->GetPawn());
}

void ARPGGameDataCopy::CheckQuest()
{
	FRPGQuestQuickInfo QuestInfo = _CheckStat->GetQuestQuickInfo();
	if (_QuestQuickInfo.TimeStamp == QuestInfo.TimeStamp)return;
	_QuestQuickInfo = QuestInfo;
}

void ARPGGameDataCopy::CheckCharacterStat()
{
	TSharedPtr<FCharacterStat> CharacterStat = _CheckStat->GetCharacterStat();
	if (CharacterStat->TimeStamp == _CharacterStat->TimeStamp)
		return;
	_CharacterStat->SetInfo(CharacterStat);
}

void ARPGGameDataCopy::CheckCharacterItems()
{
	URPGGameCharacterBagComponent* BagComoponent = _CheckStat->GetCharacterBag();
	TArray<TSharedPtr<FRPGItemInfo>> CharacterItems = BagComoponent->GetChartacterItems();
	if (_CharacterItemInfo.Num() != CharacterItems.Num())
	{
		_CharacterItemInfo = CharacterItems;
		_bInitFirstItem = true;
		return;
	}
	for (int i = 0; i < CharacterItems.Num(); i++)
	{
		if (CharacterItems[i]->TimeStamp == _CharacterItemInfo[i]->TimeStamp)
			continue;
		_CharacterItemInfo[i] = CharacterItems[i];
		_bInitFirstItem = true;
	}
}

void ARPGGameDataCopy::CheckAddLog()
{
	auto ExpLog = _CheckStat->GetAddExpLog();
	if (ExpLog.Num() != 0)
	{
		_AddExpLog += ExpLog;
		_CheckStat->RemoveAddExpLog();
	}
	URPGGameCharacterBagComponent* BagComoponent = _CheckStat->GetCharacterBag();
	auto GoldLog = BagComoponent->GetAddGoldLog();
	if (GoldLog.Num() != 0)
	{
		_AddGoldLog += GoldLog;
		BagComoponent->RemoveAddGoldLog();
	}
}

void ARPGGameDataCopy::CehckkCharacterMoney()
{
	auto Money = _CheckStat->GetCharacterBag()->GetCharacterMoney();
	if (_CharacterMoney->TimeStamp == Money->TimeStamp)
		return;
	_CharacterMoney = Money;
}

void ARPGGameDataCopy::CheckCharacterSkillCoolDown()
{
	auto Skills = _Character->GetSkills();
	if (_CharacterSkillInfo.Num() != Skills.Num())
	{
		for (int i = 0; i < Skills.Num(); i++)
		{
			if (FindSkill(Skills[i]->GetName()) == true) continue;

			TSharedPtr<FGameSkillDataCopyInfo> NewSkillCopy = MakeShareable(new FGameSkillDataCopyInfo);
			NewSkillCopy->CoolDown = Skills[i]->GetCoolDown();
			NewSkillCopy->CurrentCoolDown = Skills[i]->GetCurrentCoolDown();
			NewSkillCopy->TimeStamp = Skills[i]->GetTimeStamp();
			NewSkillCopy->Identify = Skills[i]->GetInputKeyIdentify();
			NewSkillCopy->Name = Skills[i]->GetName();
			NewSkillCopy->SkillState = Skills[i]->GetESkillState();
			_CharacterSkillInfo.Add(NewSkillCopy);
		}
	}
	else
	{
		for (int i = 0; i < Skills.Num(); i++)
		{
			auto CopyInfo = FindCopySkillInfo(Skills[i]->GetName());
			if (CopyInfo == nullptr) continue;
			if (CopyInfo->TimeStamp == Skills[i]->GetTimeStamp()) continue;

			CopyInfo->CoolDown = Skills[i]->GetCoolDown();
			CopyInfo->CurrentCoolDown = Skills[i]->GetCurrentCoolDown();
			CopyInfo->Identify = Skills[i]->GetInputKeyIdentify();
			CopyInfo->Name = Skills[i]->GetName();
			CopyInfo->SkillState = Skills[i]->GetESkillState();
			CopyInfo->TimeStamp = Skills[i]->GetTimeStamp();
		}
	}
}

bool ARPGGameDataCopy::FindSkill(const FName& SkillName)
{
	bool bExistSkill = false;
	for (int i = 0; i < _CharacterSkillInfo.Num(); i++)
	{
		if (_CharacterSkillInfo[i]->Name == SkillName)
		{
			bExistSkill = true;
			break;
		}
	}
	return bExistSkill;
}

TSharedPtr<FGameSkillDataCopyInfo> ARPGGameDataCopy::FindCopySkillInfo(const FName& SkillName)
{
	for (int i = 0; i < _CharacterSkillInfo.Num(); i++)
	{
		if (_CharacterSkillInfo[i]->Name == SkillName)
		{
			return _CharacterSkillInfo[i];
		}
	}
	return nullptr;
}

// Called every frame
void ARPGGameDataCopy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_DeltaTime += DeltaTime;
	if (_DeltaTime < STARNDARD_TIME)
		return;

	CheckCharacterStat();
	CheckCharacterItems();
	CehckkCharacterMoney();
	CheckCharacterSkillCoolDown();
	CheckAddLog();
	CheckQuest();
	_DeltaTime = 0.f;
}

