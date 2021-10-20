// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameGetInfoLayout.generated.h"

class URPGameFadeTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameGetInfoLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	TArray<URPGameFadeTextBlock*> _TextBlocks;
	bool _bFirstInit;
public:
	virtual void NativeConstruct() override;
	void UpdateFadeText();
	void SetGetInfoText(int New, bool bGold);
};
