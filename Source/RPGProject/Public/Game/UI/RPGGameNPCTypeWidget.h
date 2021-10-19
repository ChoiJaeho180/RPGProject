// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameNPCTypeWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameNPCTypeWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* _NPCTypeText;
public:
	virtual void NativeConstruct() override;

	void SetTypeText(const FString& Text);
};
