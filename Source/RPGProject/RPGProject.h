// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

#define RPGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define RPGLOG_S(Verbosity) UE_LOG(RPGProject, Verbosity, TEXT("%s"), *RPGLOG_CALLINFO)
#define RPGLOG(Verbosity, Format, ...) UE_LOG(RPGProject, Verbosity, TEXT("%s %s", *RPGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)))