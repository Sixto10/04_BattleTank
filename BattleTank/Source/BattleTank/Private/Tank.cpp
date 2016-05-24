// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerState.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pointers not protected as in constructor, unlikely to fail
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aim Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ATank::AddAmmo(int Rounds)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Rounds, 0, MaxAmmo);
}

const int ATank::GetRoundsLeft()
{
	return CurrentAmmo;
}

void ATank::SetAimIntention(FVector WorldSpaceAim)
{
	TankAimingComponent->SetAimIntention(WorldSpaceAim); // Delegate to tank
}

const float ATank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::BlowUpTank()
{
	// Blown-up tanks have no controller
	if (!GetController()) {
		return;
	}

	bool bIsPlayer = GetController()->GetClass()->IsChildOf(APlayerController::StaticClass());
	if (bIsPlayer)
	{
		auto Controller = GetController()->CastToPlayerController();
		Controller->StartSpectatingOnly();
	}
	else // AI tank
	{
		DetachFromControllerPendingDestroy();
	}
	FindComponentByClass<UParticleSystemComponent>()->Activate();
	OnTankDeath.Broadcast();
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// We want hit points so we're clear on when health is zero
	int DamagePoints = FMath::Round(DamageAmount);

	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		BlowUpTank();
	}
	return DamageToApply;
}

const bool ATank::IsBarrelMoving()
{
	// Delegate to aiming component
	return TankAimingComponent->IsBarrelMoving();
}

void ATank::Fire()
{
	return TankAimingComponent->Fire();
}