// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameHuntMapInfo.h"
#include "Game/Enemy/RPGGameEnemyDog.h"

URPGGameHuntMapInfo::URPGGameHuntMapInfo()
{
	GameEnemyDogClass = ARPGGameEnemyDog::StaticClass();
}
