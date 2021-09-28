// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameUserInfoLayout.generated.h"

class URPGGameProgressBarLayout;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUserInfoLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameProgressBarLayout* _HPBar;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
};
