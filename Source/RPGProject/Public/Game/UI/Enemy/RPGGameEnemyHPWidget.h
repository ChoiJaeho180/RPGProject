// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameEnemyHPWidget.generated.h"

class UProgressBar;
class URPGGameEnemyStatComponent;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEnemyHPWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	TWeakObjectPtr<URPGGameEnemyStatComponent> _CurrentCharacterStat;
	UPROPERTY()
	UProgressBar* _HPProgressBar;
public:
	virtual void NativeConstruct() override;
	void BindCharacterStat(URPGGameEnemyStatComponent* NewStat);
	void UpdateHPWidget();

};
