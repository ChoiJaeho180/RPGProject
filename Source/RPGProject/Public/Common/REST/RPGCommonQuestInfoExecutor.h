// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "RPGCommonQuestInfoExecutor.generated.h"

UCLASS()
class RPGPROJECT_API ARPGCommonQuestInfoExecutor : public ARPGCommonBaseExecutor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCommonQuestInfoExecutor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Update(TSharedPtr<FJsonObject>& RestMsg);
};
