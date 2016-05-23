// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector HitLocation;
	if (CastSightRay(HitLocation) && GetPawn())
	{
		Cast<ATank>(GetPawn())->SetAimIntention(HitLocation);
	}
}

bool ATankPlayerController::CastSightRay(FVector &HitLocation)
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
			DrawDebugPoint(GetWorld(), HitLocation, 10, FColor(255, 0, 255), false, 0.0);
			return true;
		}
	}
	return false;
}

