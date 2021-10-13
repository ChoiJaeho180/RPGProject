// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Pawn.h"
#include "RPGGameEnemyBase.generated.h"

class UWidgetComponent;
class URPGGameEnemyStatComponent;

UCLASS()
class RPGPROJECT_API ARPGGameEnemyBase : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	USkeletalMeshComponent* _SkeletalMeshCompo;
	UPROPERTY()
	UCapsuleComponent* _CapsuleCompo;
	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* _HPBarWidget;
	UPROPERTY()
	URPGGameEnemyStatComponent* _EnemyStatComponent;
public:
	// Sets default values for this pawn's properties
	ARPGGameEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Init();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
