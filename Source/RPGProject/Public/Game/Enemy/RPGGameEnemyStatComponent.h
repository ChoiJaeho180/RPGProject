// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/ActorComponent.h"
#include "RPGGameEnemyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGPROJECT_API URPGGameEnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	float _CurrentHP;
	float _MaxHP;
	int _DropExp;
	int _AverageGold;
	int _Level;
	TArray<int> _BaseAttack;
	EEnemyType _EnemyType;
	int _CurrentAttackDamage;
public:	
	// Sets default values for this component's properties
	URPGGameEnemyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init(int HP, EEnemyType Type, int Exp, int AvegGold, TArray<int> BaseAttack);
	void Response();
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetHPRatio() const;
	void SetCurrentBaseAttackDamage(int index);
	int GetGold();
public:
	FORCEINLINE int GetLevel() { return _Level; }
	FORCEINLINE int GetExp() { return _DropExp; }
	FORCEINLINE int GettCurrentAttack() { return _CurrentAttackDamage; }
	FORCEINLINE TArray<int> GetAttack() { return _BaseAttack; }
	FORCEINLINE EEnemyType GetEnemyType() { return _EnemyType; }
public:
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
		
};
