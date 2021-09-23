// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "RPGCommonRestLoginExecutor.h"
#include "RPGCommonNewCharacterExecutor.h"
#include "RPGCommonCharacterInfoExecutor.h"
#include "GameFramework/Actor.h"
#include "RPGCommonRestExecutorElements.generated.h"

class ARPGCommonBaseExecutor;

DECLARE_DELEGATE_OneParam(FSetTokenDelegate, const FString&);

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
	void SetToken(const FString& Token);
public:	
	// Called every frame
	void Update(TSharedPtr<FJsonObject>& JsonObject);
public:
	FSetTokenDelegate delegateSetToken;
public:
	TSubclassOf<ARPGCommonRestLoginExecutor> RestApiLoginExecutorClass;
	TSubclassOf<ARPGCommonNewCharacterExecutor> RestApiNewCharacterExecutorClass;
	TSubclassOf<ARPGCommonCharacterInfoExecutor> RestApiCharacterInfoExecutorClass;
};
