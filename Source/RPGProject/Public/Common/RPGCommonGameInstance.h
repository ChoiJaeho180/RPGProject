// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Common/REST/RPGCommonRestRequest.h"
#include "Engine/GameInstance.h"
#include "RPGCommonGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	TUniquePtr<FRPGCommonRestRequest> _RestApiRequestor;
public:
	URPGCommonGameInstance();
	virtual void Init() override;
};
