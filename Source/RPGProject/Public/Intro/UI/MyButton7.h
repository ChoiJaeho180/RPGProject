// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton7.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

/**
 * 
 */
UCLASS()
class RPGPROJECT_API UMyButton7 : public UButton
{
	GENERATED_BODY()
		int asd2 = 0;
public:
	UMyButton7();
	void asd();
	void asdsad();

	UPROPERTY()
		FClickDelegate click;

	void OnClick();
};
