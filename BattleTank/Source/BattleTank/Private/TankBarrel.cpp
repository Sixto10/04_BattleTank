// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float Throw)
{
	auto ElevationChange = Throw * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto UnclampedElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp(UnclampedElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
