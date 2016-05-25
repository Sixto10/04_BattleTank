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
	

protected:
	UFUNCTION(BlueprintPure, Category = General)
	ATank* GetControlledTank() const;

private:
	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

	UFUNCTION()
	void OnTankDeath();
	
	// Returns an OUT parameter, and true if hit
	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	virtual void SetPawn(APawn* InPawn) override;

	// Determines when the aiming line trace stops looking for a hit
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
