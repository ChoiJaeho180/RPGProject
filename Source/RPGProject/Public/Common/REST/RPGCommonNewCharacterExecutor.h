// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "RPGCommonNewCharacterExecutor.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGCommonNewCharacterExecutor : public ARPGCommonBaseExecutor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ARPGCommonNewCharacterExecutor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Update(TSharedPtr<FJsonObject>& RestMsg);
};
