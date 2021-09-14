// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfo.h"
#include "Intro/UI/RPGIntroGetChooseScarecrow.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLobbyInfoLayout.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLobbyInfoLayout : public URPGIntroBaseLayout, public IRPGIntroLobbySlotInfo, public IRPGIntroGetChooseScarecrow
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<URPGIntroLobbySlotInfoLayout*> _CharacterSlotInfo;
	UPROPERTY()
	URPGIntroLobbySlotInfoLayout* _ChooseSlotInfo;
public:
	void UpdateChooseSlot(const int& iScarecrowIndex, const FString& Name);
	virtual void NativeConstruct() override;
	virtual void SetSlotInfo() override;

	virtual void SetCharacterName(const FString& NewName) override;
	virtual FString GetCharacterName() override;

	virtual void SetScarecrowIndex(const int& NewIndex) override;
	virtual int GetScarecrowIndex() override;
};
