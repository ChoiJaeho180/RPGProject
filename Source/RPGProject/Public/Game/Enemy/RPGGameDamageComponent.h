// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Components/ActorComponent.h"
#include "RPGGameDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGPROJECT_API URPGGameDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGGameDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AttachWidget(int Damage, APlayerController* Controller, FVector MonsterLocation);
public:
	TSubclassOf<UUserWidget> DamageWidgetClass;
};
