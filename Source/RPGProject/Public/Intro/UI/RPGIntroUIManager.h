// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGIntroUIManager.generated.h"

class URPGIntroMainWidget;
class ARPGIntroController;
UCLASS()
class RPGPROJECT_API ARPGIntroUIManager : public AActor
{
	GENERATED_BODY()
	
private:
	URPGIntroMainWidget* _IntroMainWidget;
	ARPGIntroController* _CurrentController;
public:	
	// Sets default values for this actor's properties
	ARPGIntroUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void Initialize(ARPGIntroController* NewController);
public:
	TSubclassOf<URPGIntroMainWidget> _IntroTitleWidgetClass;
};
