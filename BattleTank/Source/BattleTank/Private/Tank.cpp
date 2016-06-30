// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::BeginPlay()
{
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>(); // must be this late
}

void ATank::AimAt(FVector HitLocation)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank can't find aiming component"))
	}
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}