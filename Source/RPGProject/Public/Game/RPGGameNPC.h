// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Pawn.h"
#include "RPGGameNPC.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGameNPC : public APawn
{
	GENERATED_BODY()
private:
	UPROPERTY()
	USkeletalMeshComponent* _SkeletalMesh;

public:
	// Sets default values for this pawn's properties
	ARPGGameNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
