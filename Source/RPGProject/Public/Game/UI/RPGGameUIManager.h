// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGGameUIManager.generated.h"

class URPGCommonFade;
class URPGCommonBaseEffect;
class ARPGGameController;
class URPGGameMainWidget;

UCLASS()
class RPGPROJECT_API ARPGGameUIManager : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGCommonBaseEffect* _GameFadeEffect;
	UPROPERTY()
	ARPGGameController* _CurrentController;
	UPROPERTY()
	URPGGameMainWidget* _MainWidget;
public:	
	// Sets default values for this actor's properties
	ARPGGameUIManager();
	void Initialize(ARPGGameController* NewController);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateLevel();
	void ChangeWidget();
public:
	TSubclassOf<URPGCommonFade> IntroFadeClass;
	TSubclassOf<URPGGameMainWidget> GameMainClass;
};
