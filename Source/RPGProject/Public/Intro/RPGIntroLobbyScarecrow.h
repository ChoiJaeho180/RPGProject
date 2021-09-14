// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Pawn.h"
#include "RPGIntroLobbyScarecrow.generated.h"

class URPGIntroScarecrowAnimInstance;

UCLASS()
class RPGPROJECT_API ARPGIntroLobbyScarecrow : public APawn
{
	GENERATED_BODY()
private:
	UPROPERTY()
	USkeletalMeshComponent* _SkeletalMesh;
	UPROPERTY()
	UCapsuleComponent* _Collision;
	UPROPERTY()
	URPGIntroScarecrowAnimInstance* _AnimInstance;
public:
	// Sets default values for this pawn's properties
	ARPGIntroLobbyScarecrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateChooseAnim(bool bNews);
	UFUNCTION()
	void OnNextLevelEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	TSubclassOf<URPGIntroScarecrowAnimInstance> IntroScarecrowClass;
};
