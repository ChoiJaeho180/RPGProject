// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameDataTable.h"
#include "GameFramework/Actor.h"
#include "RPGGameBaseEffect.generated.h"

DECLARE_DELEGATE(FOnReadyCoolDownSkillDelegate);
UCLASS()
class RPGPROJECT_API ARPGGameBaseEffect : public AActor
{
	GENERATED_BODY()
protected:
	FGameSkillType _SkillInfo;
	FString _InputKeyIdentify;
	float _CoolDown;
	float _CurrentCoolDown;
	ESkillState _SkillState;
	int _TimeStamp;
	bool _bSpecialSkill;
public:	
	// Sets default values for this actor's properties
	ARPGGameBaseEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Init() {};
	virtual void ApplyProperty(ACharacter* pawn) {};
	virtual void RestoreProperty(ACharacter* pawn) {};
public:
	FOnReadyCoolDownSkillDelegate delegateReadyCoolDownSkill;
public:
	FORCEINLINE void SetInputKeyIdentify(const FString& Identify) {_InputKeyIdentify = Identify; }
	FORCEINLINE FString GetInputKeyIdentify() { return _InputKeyIdentify; }
	FORCEINLINE ESkillState GetESkillState() { return _SkillState; }
	FORCEINLINE void SetESkillState(ESkillState NewSkillState) { _SkillState = NewSkillState; _TimeStamp++; }
	FORCEINLINE float GetCoefficient() { return _SkillInfo._Coefficient; }
	FORCEINLINE float GetAttackRadius() { return _SkillInfo._AttackRadius; }
	FORCEINLINE float GetAttackLocation() { return _SkillInfo._AttackLocation; }
	FORCEINLINE float GetCoolDown() { return _SkillInfo._CoolDown; }
	FORCEINLINE float GetCurrentCoolDown() { return _CurrentCoolDown; }
	FORCEINLINE int GetTimeStamp() { return _TimeStamp; }
	FORCEINLINE int GetConsumeMP() { return _SkillInfo._MP; }
	FORCEINLINE FName GetName() { return _SkillInfo.Name; }
	FORCEINLINE bool GetSpecialState() { return _bSpecialSkill; }
	FORCEINLINE void SetSpecialState(bool bNew) {_bSpecialSkill = bNew; }
};
