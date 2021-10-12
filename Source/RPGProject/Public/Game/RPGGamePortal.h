// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameDataTable.h"
#include "GameFramework/Actor.h"
#include "RPGGamePortal.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGamePortal : public AActor
{
	GENERATED_BODY()
private:
	UBoxComponent* _Collision;

	FString _NextMap;
	FVector _NextPosition;
public:	
	// Sets default values for this actor's properties
	ARPGGamePortal();
	void Init(FPortalInfo* Data);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE FString GetNextMap() { return _NextMap; }
	FORCEINLINE FVector GetNextPosition() { return _NextPosition; }
};
