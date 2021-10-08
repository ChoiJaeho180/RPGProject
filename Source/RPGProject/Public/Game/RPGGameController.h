// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Common/REST/RPGCommonCharacterInfoExecutor.h"
#include "Game/RPGGameCharacterBagComponent.h"
#include "GameFramework/PlayerController.h"
#include "RPGGameController.generated.h"

class ARPGGameUIManager;
class ARPGGameCharacter;
class ARPGGamePlayerState;

DECLARE_DELEGATE_OneParam(FUIInteractionDelegate, EInventoryUIType);
DECLARE_DELEGATE_OneParam(FUIInputActionBarDelegate, FString);
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	ARPGGameUIManager* _GameUIManager;
	UPROPERTY()
	ARPGGameCharacter* _Character;
	UPROPERTY()
	ARPGGamePlayerState* _PlayerStat;
public:
	ARPGGameController();
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;
	void InitItemData(const TArray<FRPGRestItem>& RestItemData);
protected:
	void Move();
	void MoveToMouseCursor();
	void SetNewMoveDestination(FHitResult Hit);
public:
	
	void SendActiveMap(const FString& MapName);
	void SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo);

	void LeftMouseClick();
	void InteractionUI(EInventoryUIType InteractionType);
	void InteractionPortionBarUI(FString Key);
public:
	FORCEINLINE ARPGGamePlayerState* GetGamePlayerState() { return _PlayerStat; };
public:
	TSubclassOf<ARPGGameUIManager> RPGGameUIManagerClass;

};
