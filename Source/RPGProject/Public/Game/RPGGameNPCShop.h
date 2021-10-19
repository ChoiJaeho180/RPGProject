// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameNPC.h"
#include "RPGGameNPCShop.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameNPCShop : public ARPGGameNPC
{
	GENERATED_BODY()
private:
	
public:
	ARPGGameNPCShop();
	virtual void BeginPlay() override;

};
