// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGmaeDragBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameEquipmentLayout.generated.h"

class URPGGameTitleBarLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEquipmentLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
public:
	virtual void NativeConstruct() override;
};
