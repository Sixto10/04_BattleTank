// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float Speed)
{
	auto PitchThisFrame = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = FRotator(PitchThisFrame, 0, 0);
	AddLocalRotation(Rotation);
}
