// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameSetQuestUIInfo.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameQuestLayout.generated.h"

class URPGGameQuestSpeechLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameQuestLayout : public URPGGameBaseLayout, public IRPGGameSetQuestUIInfo
{
	GENERATED_BODY()
private:
	bool _bFirstInit;
	URPGGameQuestSpeechLayout* _QuestSpeechLayout;

public:
	virtual void NativeConstruct() override;
	void SetQuestInfo(const FRPGQuestInfo& QuestInfo);
	UFUNCTION()
	void SendQuestToMainWidget(bool bQuestPositive, FRPGQuestQuickInfo& QuestQuickInfo);
public:
};
