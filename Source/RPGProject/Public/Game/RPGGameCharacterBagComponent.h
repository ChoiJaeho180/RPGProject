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
	TSharedPtr<FMoney> _Money;
	TArray<int> _AddGoldLog;
public:	
	// Sets default values for this component's properties
	URPGGameCharacterBagComponent();
	void InitData(const TArray<FRPGRestItem>& RestItemData, const TMap<FString, FString>& MoneyData);

	void UpdateMoney(int AddMoney, bool bAddLog);
	void AddItem(const TSharedPtr<FRPGItemInfo>& NewItem);
	void RemoveItem(const TSharedPtr<FRPGItemInfo>& NewItem);
	bool RemoveItem(FName Name, int Count);
	TSharedPtr<FRPGItemInfo> FindItem(FName Name);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	FORCEINLINE TArray<int> GetAddGoldLog() { return _AddGoldLog; }
	FORCEINLINE void RemoveAddGoldLog() { _AddGoldLog.Empty(); }
	FORCEINLINE TArray<TSharedPtr<FRPGItemInfo>> GetChartacterItems() { return _CharacterItems; }
	FORCEINLINE TSharedPtr<FMoney> GetCharacterMoney() { return _Money; }
};
