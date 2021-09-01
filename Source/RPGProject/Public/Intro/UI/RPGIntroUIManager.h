// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGIntroUIManager.generated.h"

class URPGIntroBaseWidget;
class URPGIntroMainWidget;
class URPGIntroLobbyWidget;
class ARPGIntroController;

UCLASS()
class RPGPROJECT_API ARPGIntroUIManager : public AActor
{
	GENERATED_BODY()
	
private:
	URPGIntroBaseWidget* _IntroCurrentWidget;
	TMap<EIntroUIWidgetState, URPGIntroBaseWidget*> _IntroWidgetMap;
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
	UFUNCTION()
	void UpdateWidget(const EIntroUIWidgetState& NewWidgetState);
public:
	TSubclassOf<URPGIntroMainWidget> _IntroTitleWidgetClass;
	TSubclassOf<URPGIntroLobbyWidget> _IntroLobbyWidgetClass;
};
