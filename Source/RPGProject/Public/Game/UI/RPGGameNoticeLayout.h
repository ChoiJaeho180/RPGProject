// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameNoticeLayout.generated.h"

class UScaleBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameNoticeLayout : public UUserWidget
{
	GENERATED_BODY()
private:
		UPROPERTY()
	UWidgetAnimation* _NoticeAnimation;
	UPROPERTY()
	UScaleBox* _NoticeScaleBox;
	UPROPERTY()
	UTextBlock* _NoticeText;
public:
	void PlayNoticeAnimation();
	virtual void NativeConstruct() override;
	UWidgetAnimation* GetAnimation(const FString& AnimName);
	void SetNoticeText(FText Text);
};
