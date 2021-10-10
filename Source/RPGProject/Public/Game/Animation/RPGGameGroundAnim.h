// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameGroundAnim.generated.h"

class ARPGGameController;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameGroundAnim : public UObject
{
	GENERATED_BODY()
private:
	bool _bUpdateMultipleMovePoint;
	FVector_NetQuantize _MovePoint;
	ARPGGameController* _Controller;
public:
	void Update(FVector PawnLocation, EWarriorGroundAnimType& GroundState);
	void MovePoint();
	void Init(ARPGGameController* NewController);
public:
	FORCEINLINE void SetMovePoint(FVector_NetQuantize MovePoint) { _MovePoint = MovePoint; }
	FORCEINLINE FVector_NetQuantize GetMovePoint() { return _MovePoint; }

	FORCEINLINE void SetbUpdateMultipleMovePoint(bool bNew) { _bUpdateMultipleMovePoint = bNew; }
	FORCEINLINE bool GetbUpdateMultipleMovePoint() { return _bUpdateMultipleMovePoint; }
};
