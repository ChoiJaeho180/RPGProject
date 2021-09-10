// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "RPGCommonRestLoginExecutor.h"
#include "RPGCommonNewCharacterExecutor.h"
#include "GameFramework/Actor.h"
#include "RPGCommonRestExecutorElements.generated.h"

class ARPGCommonBaseExecutor;

UCLASS()
class RPGPROJECT_API ARPGCommonRestExecutorElements : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<ARPGCommonBaseExecutor*> _RestApiExecutors;
public:	
	// Sets default values for this actor's properties
	ARPGCommonRestExecutorElements();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void Update(TSharedPtr<FJsonObject>& JsonObject);
public:
	TSubclassOf<ARPGCommonRestLoginExecutor> RestApiLoginExecutorClass;
	TSubclassOf<ARPGCommonNewCharacterExecutor> RestApiNewCharacterExecutorClass;
};
