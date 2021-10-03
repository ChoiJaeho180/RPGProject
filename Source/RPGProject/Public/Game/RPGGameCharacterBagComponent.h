// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Components/ActorComponent.h"
#include "RPGGameCharacterBagComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGPROJECT_API URPGGameCharacterBagComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	TArray<TSharedPtr<FRPGItemInfo>> _CharacterItems;
public:	
	// Sets default values for this component's properties
	URPGGameCharacterBagComponent();

	void AddItem(const TSharedPtr<FRPGItemInfo>& NewItem);
	void RemoveItem(const TSharedPtr<FRPGItemInfo>& NewItem);
	TSharedPtr<FRPGItemInfo> FindItem(const TSharedPtr<FRPGItemInfo>& NewItem);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TestInfo();
public:
	FORCEINLINE TArray<TSharedPtr<FRPGItemInfo>> GetChartacterItems() { return _CharacterItems; }
};
