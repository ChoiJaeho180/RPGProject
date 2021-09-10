// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGCommonRestManager.generated.h"

class ARPGCommonRestRequestor;
class ARPGCommonRestExecutorElements;

UCLASS()
class RPGPROJECT_API ARPGCommonRestManager : public AActor
{
	GENERATED_BODY()
private:
	bool _bEndedGame = false;

	UPROPERTY()
	ARPGCommonRestRequestor* _RestApiRequestor;
	UPROPERTY()
	ARPGCommonRestExecutorElements* _RestExecutorElements;

	TQueue<TSharedPtr<FJsonObject>> _RestApiMsg;
public:	
	// Sets default values for this actor's properties
	ARPGCommonRestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Update();
	bool PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject);
	void PushQueue(TSharedPtr<FJsonObject>& JsonObject);
public:
	void Release();
public:
	TSubclassOf<ARPGCommonRestRequestor> RestApiRequestorClass;
	TSubclassOf<ARPGCommonRestExecutorElements> RestApiElementsClass;

};
