// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/GameMode.h"
#include "RPGIntroGameMode.generated.h"

class ARPGIntroController;
class ARPGIntroLobbyScarecrow;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGIntroGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	TMap<EIntroUIWidgetState, FString> _PlayerStartPoint;

	UPROPERTY()
	ARPGIntroController* _IntroController;
	UPROPERTY()
	TArray<ARPGIntroLobbyScarecrow*> _IntroLobbyScarecrows;
	TArray<FTransform> _LobbyScarecrowsPoint;
	bool _bNormalLevelTransform;
public:
	ARPGIntroGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	void SetPlayerStart(EIntroUIWidgetState NewState);
	void CreateLobbyScarecrow(const TArray<TSharedPtr<FJsonValue>>& Info);
	void UpdateChooseAnim(const int& ScarecrowIndex);
	void ChangeLevel();
public:
	TSubclassOf<ARPGIntroLobbyScarecrow> LobbyScarecrowClass;
};
