// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/Actor.h"
#include "RPGCommonBaseExecutor.generated.h"
/**
 * 
 */

UCLASS()
class RPGPROJECT_API ARPGCommonBaseExecutor : public AActor
{
	GENERATED_BODY()
protected:
	FString _RestMsgIdentify;
	
public:
	ARPGCommonBaseExecutor();
	void BeginPlay() override;
	virtual void Update(TSharedPtr<FJsonObject>& RestMsg);

	FORCEINLINE void SetRestIdentify(FString RestIdentify) { _RestMsgIdentify = RestIdentify; }
	FORCEINLINE FString GetRestIdentify() {return _RestMsgIdentify;}
};
