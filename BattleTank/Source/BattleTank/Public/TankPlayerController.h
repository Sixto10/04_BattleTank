// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	// Returns an OUT parameter, and true if hit
	const bool CastSightRay(FVector &HitLocation); //		TODO review

	// Determines when the aiming line trace stops looking for a hit
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
