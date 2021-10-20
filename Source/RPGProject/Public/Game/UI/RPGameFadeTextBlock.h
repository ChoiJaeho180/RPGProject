// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "RPGameFadeTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGameFadeTextBlock : public UTextBlock
{
	GENERATED_BODY()
private:
	bool _bActiveFade;
	float _CurrentFadeRatio;
public:
	void Update();
	void SetOpacity(float Opacity);
	FText GetLogText();
	void SetLogText(FText NewText);
	FORCEINLINE bool GetbActive() { return _bActiveFade; }
	FORCEINLINE void SetbActive(bool bNewState) { _bActiveFade = bNewState; }
};
