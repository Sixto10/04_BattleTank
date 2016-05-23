// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float Speed)
{
	auto YawThisFrame = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = FRotator(0, YawThisFrame, 0);
	AddLocalRotation(Rotation);
}