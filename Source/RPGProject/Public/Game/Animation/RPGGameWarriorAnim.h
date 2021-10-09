// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGGameWarriorAnim.generated.h"

class URPGGameGroundAnim;

UENUM(BlueprintType)
enum class EWarriorAnimType : uint8
{
	GROUND UMETA(DisplayName = "GROUND"),
	NONE UMETA(DisplayName = "NONE"),
};

UENUM(BlueprintType)
enum class EWarriorGroundAnimType : uint8
{
	RUN_START UMETA(DisplayName = "RUN_START"),
	RUN_LOOP UMETA(DisplayName = "RUN_LOOP"),
	RUN_END UMETA(DisplayName = "RUN_END"),
	IDLE UMETA(DisplayName = "IDLE"),
	NONE UMETA(DisplayName = "NONE"),
};


/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameWarriorAnim : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameGroundAnim* _GroundAnim;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EWarriorAnimType _WarriorAnimType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn1, Meta = (AllowPrivateAccess = true))
	EWarriorGroundAnimType _WarriorGroundAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _bIsDead;
public:
	URPGGameWarriorAnim();
	void Init();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void OnClickedMove(FVector_NetQuantize MovePoint);
public:
	FORCEINLINE EWarriorAnimType GetWarriorAnimType() { return _WarriorAnimType; }
	FORCEINLINE void SetGroundAnimType(EWarriorGroundAnimType NewType) { _WarriorGroundAnimType = NewType; }
	FORCEINLINE EWarriorGroundAnimType GetGroundAnimType() { return _WarriorGroundAnimType; }
	FORCEINLINE URPGGameGroundAnim* GetGroundAnim() { return _GroundAnim; }
};
