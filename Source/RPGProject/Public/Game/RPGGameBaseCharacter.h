// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Character.h"
#include "RPGGameBaseCharacter.generated.h"

class UDecalComponent;

UCLASS()
class RPGPROJECT_API ARPGGameBaseCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
		/** A decal that projects to the cursor location. */
	UPROPERTY()
	UDecalComponent* _CursorToWorld;
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta=(AllowPrivateAccess=true))
	USpringArmComponent* _SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* _Camera;

	FVector _MoveFV;
	FRotator _MoveR;
	const FVector _InitDecalSize = FVector(16.f, 35.f, 35.f);
	const FVector _FinishDecalSize = FVector(16.f, 0.f, 0.f);
	float _DecalRatio = 0.f;
	bool _bInputMove = false;
public:
	// Sets default values for this character's properties
	ARPGGameBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitDecalSize();
	void InitDecalPostionAndRotation(FHitResult result);
public:
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return _CursorToWorld; }
	FORCEINLINE void SetbInputMove(bool bNew = false) { _bInputMove = bNew; }
};
