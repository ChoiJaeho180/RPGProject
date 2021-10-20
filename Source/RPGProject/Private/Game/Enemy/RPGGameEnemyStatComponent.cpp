// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyStatComponent.h"


// Sets default values for this component's properties
URPGGameEnemyStatComponent::URPGGameEnemyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGGameEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void URPGGameEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URPGGameEnemyStatComponent::Init(int HP, EEnemyType Type, int Exp, int AvegGold, TArray<int> BaseAttack)
{
	_CurrentHP = _MaxHP = HP;
	_DropExp = Exp;
	_EnemyType = Type;
	_AverageGold = AvegGold;
	_BaseAttack = BaseAttack;
	SetHP(_CurrentHP);
}

void URPGGameEnemyStatComponent::Response()
{
	_CurrentHP = _MaxHP;
	SetHP(_CurrentHP);
}

void URPGGameEnemyStatComponent::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(_CurrentHP - NewDamage, 0.0f, _MaxHP));
}

void URPGGameEnemyStatComponent::SetHP(float NewHP)
{
	_CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	// float의 값을 0과 비교할 때는 미세한 오차 범위 내에 있는지를 보고 판단하는 것이 좋다.
	// 언리얼 엔진은 무시 가능한 오차를 측정할때 사용하도록 KINDA_SMALL_NUMBER라는 매크로를 제공한다.
	if (_CurrentHP < KINDA_SMALL_NUMBER)
	{
		_CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}

}

float URPGGameEnemyStatComponent::GetHPRatio() const
{
	return(_MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (_CurrentHP / _MaxHP);
}

void URPGGameEnemyStatComponent::SetCurrentBaseAttackDamage(int index)
{
	_CurrentAttackDamage = _BaseAttack[index];
}

int URPGGameEnemyStatComponent::GetGold()
{
	int CorrectGold = (float)_AverageGold / 20;
	return FMath::RandRange(_AverageGold - CorrectGold, _AverageGold + CorrectGold);
}

