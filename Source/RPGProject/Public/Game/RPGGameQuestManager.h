// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameQuestManager.generated.h"

DECLARE_DELEGATE_OneParam(FOnChangeQuestToMainWidgetDelegate, bool);

USTRUCT(Blueprintable)
struct FRPGQuestInfo
{
	GENERATED_USTRUCT_BODY()
public:
	
	FString NPCName;
	FString Speech;
	int QuestNumber = -1;
	int MinLevel = -1;
	bool bSuccessed;
	void SetInfo(FString NewNPCName, FString NewSpeech, int NewQuestNumber, int NewMinLevel)
	{
		NPCName = NewNPCName; Speech = NewSpeech;
		QuestNumber = NewQuestNumber;  MinLevel = NewMinLevel;
		bSuccessed = false;
	}
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
