// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameBagslot.generated.h"

class UImage;
class UButton;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameBagslot : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UImage* _Icon;
	UPROPERTY()
	UButton* _Button;
public:
	virtual void NativeConstruct() override;
};
