// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameGetUserInfo.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameUserLayout.generated.h"

class URPGGameUserInfoLayout;
class URPGGameInventoryLayout;
class UButton;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUserLayout : public URPGGameBaseLayout, public IRPGGameGetUserInfo
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameUserInfoLayout* _UserInfoLayout;
	UPROPERTY()
	URPGGameInventoryLayout* _InventoryLayout;
	UPROPERTY()
	UButton* _ExitButton;
public:
	virtual void NativeConstruct() override;
	virtual URPGGameInventoryLayout* GetUserInfoLayout() override;
	UFUNCTION()
	void ExitButton();
};
