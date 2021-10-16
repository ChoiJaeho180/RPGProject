// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameDamagerWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameDamagerWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UTextBlock* _DamageText;
	UWidgetAnimation* _FadeAnimation;
	FWidgetAnimationDynamicEvent delegateEndedEffect;
	FVector2D _InitPosition;
	FVector2D _GoalPosition;

	float _Alpha;
public:
	virtual void NativeConstruct() override;
	void SetFadeAnimation();
	void SetDamageText(FString NewText);
	void PlayFadeAnimation();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
	void OnEndedFadeInAnim();

	FORCEINLINE void SetInitPosition(FVector2D New) { _InitPosition = New;}
	FORCEINLINE void SetGoalPosition(FVector2D New) { _GoalPosition = New; }
};
