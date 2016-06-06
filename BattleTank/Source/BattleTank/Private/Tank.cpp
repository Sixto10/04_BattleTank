// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	PrimaryActorTick.bCanEverTick = false;

	// Pointers not protected as in constructor, unlikely to fail
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aim Component"));
}

void ATank::AddAmmo(int Rounds)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Rounds, 0, MaxAmmo);
}

int32 ATank::GetRoundsLeft() const
{
	return CurrentAmmo;
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation);
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::BlowUpTank()
{
	FindComponentByClass<UParticleSystemComponent>()->Activate();
	OnTankDeath.Broadcast();
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// We want hit points so we're clear on when health is zero
	int32 DamagePoints = FMath::Round(DamageAmount);

	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		BlowUpTank();
	}
	return DamageToApply;
}

bool ATank::IsBarrelMoving() const
{
	// Delegate to aiming component
	return TankAimingComponent->IsBarrelMoving();
}

void ATank::Fire()
{
	if (CurrentAmmo > 0)
	{
		TankAimingComponent->Fire();
		CurrentAmmo--;
	}
}