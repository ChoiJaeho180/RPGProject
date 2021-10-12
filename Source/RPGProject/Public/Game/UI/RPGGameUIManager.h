// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "GameFramework/Actor.h"
#include "RPGGameUIManager.generated.h"

class URPGCommonFade;
class URPGCommonBaseEffect;
class ARPGGameController;
class URPGGameMainWidget;
class URPGGameUIIdeliver;

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
	UPROPERTY()
	URPGGameUIIdeliver* _UIDeliver;
public:	
	// Sets default values for this actor's properties
	ARPGGameUIManager();
	void Initialize(ARPGGameController* NewController);
	void InitInventoryAndActionBar(const TArray<FRPGRestItem>& NewItem, const TArray<FRPGRestItem>& RestActionBar);

	void SetFadeEffectType(ECommonFadeState EffectType, bool bChangeLevel);
	void SendChangeLevel();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateLevel();
	void ChangeWidget();
	void SendInputState(const EInventoryUIType& NewInput);
	TSharedPtr<FRPGItemInfo> GetInputPortionSlotData(const FString Key);
	void ActiveShop();
	
public:
	TSubclassOf<URPGCommonFade> IntroFadeClass;
	TSubclassOf<URPGGameMainWidget> GameMainClass;
};
