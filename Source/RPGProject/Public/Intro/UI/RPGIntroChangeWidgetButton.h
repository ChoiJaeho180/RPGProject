// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/Button.h"
#include "RPGIntroChangeWidgetButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateWidgetDelegate, const EIntroUIWidgetState&, UpdateWidgetState);

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroChangeWidgetButton : public UButton
{
	GENERATED_BODY()
private:
	EIntroUIWidgetState _UpdateWidgetState;
public:
	URPGIntroChangeWidgetButton();

	FUpdateWidgetDelegate delegateUpdateWidgetClick;
	UFUNCTION()
	void OnClick();
public:
	FORCEINLINE void SetWidgetState(const EIntroUIWidgetState& NewProperty) { _UpdateWidgetState = NewProperty; }
};
