// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/Button.h"
#include "RPGIntroChangeSceneButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSceneDelegate, EIntroUIWidgetState, UpdateWidgetState);

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroChangeSceneButton : public UButton
{
	GENERATED_BODY()
private:
	EIntroUIWidgetState _UpdateProperty;

public:
	URPGIntroChangeSceneButton();

	FUpdateSceneDelegate delegateUpdateSceneClick;
	UFUNCTION()
	void OnClick();

public:
	inline void SetWidgetState(EIntroUIWidgetState NewProperty) { _UpdateProperty = NewProperty; }
};
