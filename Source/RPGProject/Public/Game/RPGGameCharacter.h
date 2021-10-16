// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/RPGGameBaseCharacter.h"
#include "RPGGameCharacter.generated.h"


UCLASS()
class RPGPROJECT_API ARPGGameCharacter : public ARPGGameBaseCharacter
{
	GENERATED_BODY()
private:
	URPGGameWarriorAnim* _WarriorAnim;
	FRotator _TargetRotator;

public:
	// Sets default values for this character's properties
	ARPGGameCharacter();
private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	void InputAttack();
	void OnClikedMove(FVector_NetQuantize MovePoint);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetHitting(FVector HitDir);
	void Dead();
	void Resurrection();
	EWarriorAnimType GetAnimState();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	FORCEINLINE URPGGameWarriorAnim* GetAnim() { return _WarriorAnim; }
	FORCEINLINE void SetRotationRow(FRotator NewRotation) { _TargetRotator = NewRotation; }
};
