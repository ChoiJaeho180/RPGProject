// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/UI/RPGGameUIInteraction.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameUserInfoLayout.generated.h"

class URPGGameProgressBarLayout;
class URPGGameActionBarLayout;
class UProgressBar;
class URPGGameSpecialBar;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUserInfoLayout : public URPGGameBaseLayout, public IRPGGameUIInteraction
{
	GENERATED_BODY()
private:
	TSharedPtr<FCharacterStat> _CharacterStat;
	UPROPERTY()
	URPGGameSpecialBar* _SpecialBar;
	UPROPERTY()
	URPGGameProgressBarLayout* _HPBar;
	UPROPERTY()
	URPGGameProgressBarLayout* _MPBar;
	UPROPERTY()
	URPGGameProgressBarLayout* _ExpBar;
	UPROPERTY()
	URPGGameActionBarLayout* _ActionBar;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void SetGameDataCopy() override;
	virtual void UpdateProperty() override;
};
