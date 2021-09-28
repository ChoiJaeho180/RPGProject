// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameProgressBarLayout.generated.h"

class URPGGameProgressBar;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameProgressBarLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameProgressBar* _ProgressBar;
public:
	virtual void NativeConstruct() override;
};
