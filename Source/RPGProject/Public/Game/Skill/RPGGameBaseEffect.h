// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGGameBaseEffect.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGameBaseEffect : public AActor
{
	GENERATED_BODY()
protected:
	FString _InputKeyIdentify;
	float _CoolDown;
	float _CurrentCoolDown;
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
	bool CheckUsableSkill();
public:
	FORCEINLINE void SetInputKeyIdentify(const FString& Identify) {_InputKeyIdentify = Identify; }
	FORCEINLINE FString GetInputKeyIdentify() { return _InputKeyIdentify; }
};
