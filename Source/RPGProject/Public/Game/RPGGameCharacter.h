// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameBaseCharacter.h"
#include "RPGGameCharacter.generated.h"

class URPGGameWarriorAnim;

UCLASS()
class RPGPROJECT_API ARPGGameCharacter : public ARPGGameBaseCharacter
{
	GENERATED_BODY()
private:
	URPGGameWarriorAnim* _WarriorAnim;
public:
	// Sets default values for this character's properties
	ARPGGameCharacter();
private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void OnClikedMove(FVector_NetQuantize MovePoint);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
