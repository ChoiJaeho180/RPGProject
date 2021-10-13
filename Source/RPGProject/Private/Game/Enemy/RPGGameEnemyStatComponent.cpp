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

void URPGGameEnemyStatComponent::SetDamage(float NewDamage)
{
}

void URPGGameEnemyStatComponent::SetHP(float NewHP)
{
	_CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	// float�� ���� 0�� ���� ���� �̼��� ���� ���� ���� �ִ����� ���� �Ǵ��ϴ� ���� ����.
	// �𸮾� ������ ���� ������ ������ �����Ҷ� ����ϵ��� KINDA_SMALL_NUMBER��� ��ũ�θ� �����Ѵ�.
	if (_CurrentHP < KINDA_SMALL_NUMBER)
	{
		_CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}

}

float URPGGameEnemyStatComponent::GetHPRatio() const
{
	return 0.0f;
	//return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

