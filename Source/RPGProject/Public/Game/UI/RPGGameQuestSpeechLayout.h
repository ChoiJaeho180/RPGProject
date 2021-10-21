// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameQuestSpeechLayout.generated.h"

class UTextBlock;
class UButton;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameQuestSpeechLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	bool _bFirstInit;

	UPROPERTY()
	UTextBlock* _SpeechText;
	UPROPERTY()
	UButton* _NegativeButton;
	UPROPERTY()
	UButton* _PositiveButton;
	UPROPERTY()
	UButton* _AcceptButton;
	
public:
	EGameQuestNPCState _QuestState;
	FRPGQuestInfo _QuestInfo;
	FString _CurrentSpeech;
	int _CurrentSpeechIndex;
	bool _bActiveSpeech;
	float _CurrentTime;
public:
	void QuestStateVisibility();
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
	void OnClickedPositiveButton();
	UFUNCTION()
	void OnClickedAcceptButton();
	UFUNCTION()
	void OnClickedNegativeeButton();
	void SetQuestInfo(const FRPGQuestInfo& QuestInfo, EGameQuestNPCState State);
public:
	FOnChangeQuestToMainWidgetDelegate delegateChangeQuestToMainWidget;
public:

};
