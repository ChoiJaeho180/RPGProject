// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameShopLayout.generated.h"

class URPGGameBagLayout;
class UButton;
class URPGGameShopBagLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameShopLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()

private:
	UPROPERTY()
	URPGGameBagLayout* _BagLayout;
	UPROPERTY()
	URPGGameShopBagLayout*  _ShopBagLayout;

public:
	virtual void NativeConstruct() override;
	void SetBagLayout(URPGGameBagLayout* BagLayout);
	void CloseButton();
};
