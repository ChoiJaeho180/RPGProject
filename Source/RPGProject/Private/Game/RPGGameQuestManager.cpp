// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RPGGameQuestManager.h"

TArray<FRPGQuestInfo> URPGGameQuestManager::GetNPCNameToQuestInfo(const FString& Name)
{
    TArray<FRPGQuestInfo> returnValue;
    for (int i = 0; i < _PreviousQuests.Num(); i++)
    {
        if (Name != _PreviousQuests[i].NPCName) continue;
        returnValue.Add(_PreviousQuests[i]);
    }
    return returnValue;
}
