// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameBaseCharacter.h"
#include "RPGGameCharacter.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGameCharacter : public ARPGGameBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGGameCharacter();
private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
};
