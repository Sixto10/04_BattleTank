// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	
	if (!GetControlledTank()) { return; }

	// Subscribe our local method to the tank's death event
	GetControlledTank()->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// TODO mention issue where aiming at sky slews barrel strangely
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		DrawDebugPoint(GetWorld(), HitLocation, 10, FColor(255, 0, 255), false, 0.0);
		// TODO change to UI element
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// TODO change to UI component
	// Get or set crosshair position
	int32 sizeX, sizeY;
	GetViewportSize(sizeX, sizeY);
	auto ScreenLocation = FVector2D(sizeX / 2, sizeY / 3);

	// TODO review this
	FVector WorldPosition, LookDirection; // TODO what dows WorldPosition return?
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenLocation, WorldPosition, LookDirection))
	{
		FHitResult HitResult;
		auto StartLocation = PlayerCameraManager->GetCameraLocation();
		auto EndLocation = StartLocation + LookDirection * LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
		{
			HitLocation = HitResult.Location;
			return true;
		}
	}
	return false;
}

// Used in BP hence in function of it's own
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}



