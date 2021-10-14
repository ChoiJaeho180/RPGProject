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
public:	
	// Sets default values for this component's properties
	URPGGameEnemyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init(int HP, EEnemyType Type, int Exp, int AvegGold);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack() const;
	float GetHPRatio() const;

public:
	FORCEINLINE int GetLevel() { return _Level; }
	FORCEINLINE int GetExp() { return _DropExp; }
public:
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
		
};
