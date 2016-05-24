// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector HitLocation;
	// TODO mention issue where aiming at sky slews barrel strangely
	// EXERCISE: Change aiming reticule to UI element linked to code
	if (GetPawn() && CastSightRay(HitLocation)) // Don't set aim if detached
	{
		GetControlledTank()->SetAimIntention(HitLocation);
		DrawDebugPoint(GetWorld(), HitLocation, 10, FColor(255, 0, 255), false, 0.0);
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Important here or we'll get strangies
	GetControlledTank()->OnTankDeath.AddDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

// Used in BP hence in function of it's own
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



bool ATankPlayerController::CastSightRay(FVector &HitLocation) const
{
	int32 sizeX;
	int32 sizeY;
	GetViewportSize(sizeX, sizeY);
	auto ScreenLocation = FVector2D(sizeX / 2, sizeY / 3);

	FVector WorldPosition;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenLocation, WorldPosition, WorldDirection))
	{
		FHitResult HitResult;
		auto StartLocation = PlayerCameraManager->GetCameraLocation();
		auto EndLocation = StartLocation + WorldDirection * LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
			HitLocation = HitResult.Location;
			return true;
		}
	}
	return false;
}

