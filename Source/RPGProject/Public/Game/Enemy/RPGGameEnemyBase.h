// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Character.h"
#include "RPGGameEnemyBase.generated.h"

class UWidgetComponent;
class URPGGameEnemyStatComponent;
class URPGGameTImer;
class URPGGameEnemyBaseAnim;
UCLASS()
class RPGPROJECT_API ARPGGameEnemyBase : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* _HPBarWidget;
	UPROPERTY()
	URPGGameEnemyStatComponent* _EnemyStatComponent;
	UPROPERTY()
	URPGGameTImer* _ActiveWidgetTimer;
	UPROPERTY()
	URPGGameEnemyBaseAnim* _Anim;
	int _DetectRadius;
	int _AttackRange;
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
	virtual void Init(int HP, EEnemyType Type, int Exp, int AvegGold, int BaseAttack);
	void SetHiddenHPWidgetBar(bool bNew);
	void GetHit();
	void Attack(bool bNew);
public:
	FORCEINLINE URPGGameEnemyBaseAnim* GetEnemyBaseAnim() { return _Anim; }
	FORCEINLINE URPGGameEnemyStatComponent* GetEnemyStatCompo() { return _EnemyStatComponent; }
	FORCEINLINE int GetDetectRadius() { return _DetectRadius; }
	FORCEINLINE int GetAttackRange() { return _AttackRange; }
};
