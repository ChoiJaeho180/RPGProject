// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Character.h"
#include "RPGGameEnemyBase.generated.h"

class UWidgetComponent;
class URPGGameEnemyStatComponent;
class URPGGameTImer;

UCLASS()
class RPGPROJECT_API ARPGGameEnemyBase : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* _HPBarWidget;
	UPROPERTY()
	URPGGameEnemyStatComponent* _EnemyStatComponent;
	URPGGameTImer* _ActiveWidgetTimer;
public:
	// Sets default values for this pawn's properties
	ARPGGameEnemyBase();
	virtual void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Init(int HP, EEnemyType Type, int Exp, int AvegGold);
	void SetHiddenHPWidgetBar(bool bNew);
public:
	FORCEINLINE URPGGameEnemyStatComponent* GetEnemyStatCompo() { return _EnemyStatComponent; }
};
