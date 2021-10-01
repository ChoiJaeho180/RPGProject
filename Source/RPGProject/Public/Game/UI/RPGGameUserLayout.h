// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameUserLayout.generated.h"

class URPGGameUserInfoLayout;
class URPGGameInventoryLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUserLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameUserInfoLayout* _UserInfoLayout;
	URPGGameInventoryLayout* _InventoryLayout;
public:
	virtual void NativeConstruct() override;
};
