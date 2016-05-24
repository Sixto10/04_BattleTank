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

public:
	UFUNCTION(BlueprintPure, Category = General)
	ATank* GetControlledTank() const;

private:
	// Returns an OUT parameter, and true if hit
	bool CastSightRay(FVector &HitLocation) const;

	// Determines when the aiming line trace stops looking for a hit
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
