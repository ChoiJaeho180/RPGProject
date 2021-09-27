// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Pawn.h"
#include "RPGGameNPC.generated.h"

class UWidgetComponent;
UCLASS()
class RPGPROJECT_API ARPGGameNPC : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	USkeletalMeshComponent* _SkeletalMesh;
	UPROPERTY()
	UWidgetComponent* _WidgetCompo;
	FVector _Position;
	FString _Village;
	FString _Name;
	FString _Type;
	TArray<FString> _Speech;
	bool _bQuestor;
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

public:
	void SetInfo(USkeletalMesh* NewSkeletalMesh, TSubclassOf<UAnimInstance> NewAnim,FVector NewPosition, FString NewVillage, FString NewName, FString NewType, bool bQuestor, TArray<FString> Speech);
};
