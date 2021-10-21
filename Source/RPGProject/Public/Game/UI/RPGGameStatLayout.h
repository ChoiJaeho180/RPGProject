// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGamePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameStatLayout.generated.h"

class URPGGameTitleBarLayout;
class ARPGGameDataCopy;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameStatLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
	UPROPERTY()
	ARPGGameDataCopy* _CheckStatData;
	UPROPERTY()
	UTextBlock* _LevelText;
	UPROPERTY()
	UTextBlock* _StxText;
	UPROPERTY()
	UTextBlock* _DexText;
	UPROPERTY()
	UTextBlock* _LukText;
	UPROPERTY()
	UTextBlock* _IntText;
	TSharedPtr<FCharacterStat> _CharacterStat;
public:
	virtual void NativeConstruct() override;
	void Tick();
};
