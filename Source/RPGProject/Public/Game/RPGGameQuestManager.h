// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameQuestManager.generated.h"

DECLARE_DELEGATE_TwoParams(FOnChangeQuestToMainWidgetDelegate, bool, FRPGQuestQuickInfo&);

USTRUCT(Blueprintable)
struct FRPGQuestInfo
{
	GENERATED_USTRUCT_BODY()
public:
	
	FString NPCName;
	FString Speech;
	int QuestNumber = -1;
	int MinLevel = -1;
	TMap<FString, int> Compensation;
	TMap<FString, int> Require;
	bool bSuccessed;
	void SetInfo(FString NewNPCName, FString NewSpeech, int NewQuestNumber, int NewMinLevel, 
				const TMap<FString, int>& NewCompensation, const TMap<FString, int>& NewRequire)
	{
		NPCName = NewNPCName; Speech = NewSpeech;
		QuestNumber = NewQuestNumber;  MinLevel = NewMinLevel;

		Compensation = NewCompensation;
		Require = NewRequire;
		bSuccessed = false;
	}
};
USTRUCT(Blueprintable)
struct FRPGQuestQuickInfo
{
	GENERATED_USTRUCT_BODY()
public:
	TMap<FString, int> Require;
	TMap<FString, int> Current;
	int QuestNumber = -1;
	int TimeStamp = -1;
};
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameQuestManager : public UObject
{
	GENERATED_BODY()
private:
	TArray<FRPGQuestInfo> _PreviousQuests;
	TArray<FRPGQuestInfo> _EnRouteQuests;
public:
	TArray<FRPGQuestInfo> GetNPCNameToQuestInfo(const FString& Name);
public:
	FORCEINLINE void AddPreviousQuest(const FRPGQuestInfo& NewQuest) { _PreviousQuests.Add(NewQuest); }
	FORCEINLINE void SetPreviousQuest(const TArray<FRPGQuestInfo>& NewQuest) { _PreviousQuests = NewQuest; }
};
