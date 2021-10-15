// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RPGGameCameraShake.h"

URPGGameCameraShake::URPGGameCameraShake()
{
    OscillationDuration = 0.15f;
    OscillationBlendInTime = 0.3f;
    OscillationBlendOutTime =0.7;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(3.0f, 3.5f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(3.5f, 4.f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(3.0f, 3.5f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(3.5f, 4.f);
}