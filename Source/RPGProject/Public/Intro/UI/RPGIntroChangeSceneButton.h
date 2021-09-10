// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/Button.h"
#include "RPGIntroChangeSceneButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSceneDelegate, EIntroDerivedWidgetState, UpdateWidgetState);

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroChangeSceneButton : public UButton
{
	GENERATED_BODY()
private:
	EIntroDerivedWidgetState _UpdateProperty;

public:
	URPGIntroChangeSceneButton();

	FUpdateSceneDelegate delegateUpdateSceneClick;
	UFUNCTION()
	void OnClick();

public:
	FORCEINLINE void SetWidgetState(EIntroDerivedWidgetState NewProperty) { _UpdateProperty = NewProperty; }
};
