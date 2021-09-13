// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "RPGCommonSetToken.h"
#include "RPGCommonBaseExecutor.h"
#include "RPGCommonRestLoginExecutor.generated.h"

UCLASS()
class RPGPROJECT_API ARPGCommonRestLoginExecutor : public ARPGCommonBaseExecutor, public IRPGCommonSetToken
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCommonRestLoginExecutor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Update(TSharedPtr<FJsonObject>& RestMsg) override;
};
