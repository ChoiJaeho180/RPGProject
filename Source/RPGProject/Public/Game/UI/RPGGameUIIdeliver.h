// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameUIIdeliver.generated.h"

class URPGGameInventoryLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUIIdeliver : public UObject
{
	GENERATED_BODY()
private:
	URPGGameInventoryLayout* _TargetUI;
public:
	void SetDeliveryTargetUI(URPGGameInventoryLayout* NewUI);
};
