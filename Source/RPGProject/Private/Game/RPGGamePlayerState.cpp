// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGamePlayerState.h"


ARPGGamePlayerState::ARPGGamePlayerState()
{
	_CharacterStat = MakeShareable(new FCharacterStat());
}
