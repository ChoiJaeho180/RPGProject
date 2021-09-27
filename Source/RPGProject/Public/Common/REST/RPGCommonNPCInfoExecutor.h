// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "RPGCommonNPCInfoExecutor.generated.h"

UCLASS()
class RPGPROJECT_API ARPGCommonNPCInfoExecutor : public ARPGCommonBaseExecutor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCommonNPCInfoExecutor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void Update(TSharedPtr<FJsonObject>& RestMsg);

};
