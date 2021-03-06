// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Character.h"
#include "RPGGameBaseCharacter.generated.h"

class UDecalComponent;
class URPGGameCameraShake;
class ARPGGameBaseEffect;

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
	UPROPERTY()
	TArray<ARPGGameBaseEffect*> _Skills;
	UPROPERTY()
	ARPGGameBaseEffect* _UseCurrentSkill;
protected:
	float _BaseAttackRadius;
	float _BaseAttackRange;

	FString _CurrentMap;
	FString _NextMap;
	FVector _NextMapPosition;
	bool _bInvincibility;
private:
	FVector _CursorMoveFV;
	FRotator _CursorMoveR;
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
	void SetTargetArmLength(float Length);
public:
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return _CursorToWorld; }
	FORCEINLINE void SetbInputMove(bool bNew = false) { _bInputMove = bNew; }
	FORCEINLINE FString GetCurrentMap() { return _CurrentMap; }
	FORCEINLINE void SetCurrentMap(const FString& NewMap) { _CurrentMap = NewMap; }
	FORCEINLINE FString GetNextMap() { return _NextMap; }
	FORCEINLINE void SetNextMap(const FString& NextMap) { _NextMap = NextMap; }
	FORCEINLINE FVector GetNextMapPosition() { return _NextMapPosition; }
	FORCEINLINE void SetNextMapPosition(const FVector& NextMapPosition) { _NextMapPosition = NextMapPosition; }

	FORCEINLINE float GetBaseAttackRadius() { return _BaseAttackRadius; }
	FORCEINLINE float GetBaseAttackRange() { return _BaseAttackRange; }

	FORCEINLINE void SetbInvincibility(bool bNew) { _bInvincibility = bNew; }
	FORCEINLINE bool GetbInvincibility() { return _bInvincibility; }
	FORCEINLINE ARPGGameBaseEffect* GetUseCurrentSkill() { return _UseCurrentSkill; }
	FORCEINLINE TArray<ARPGGameBaseEffect*> GetSkills() { return _Skills; }
public:
	UPROPERTY()
	TSubclassOf<UCameraShake> MyShake;
};
