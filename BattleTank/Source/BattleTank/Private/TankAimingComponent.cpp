// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) // Note name
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!Barrel) { return false; } // Barrel may not be attached to tank yet
	auto BarrelForward = Barrel->GetForwardVector();
	return !DesiredAimDirection.Equals(BarrelForward, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }
    
	FVector StartLocation = Barrel->GetComponentLocation();
    FVector LaunchVelocity; // Out parameter
	if (UGameplayStatics::SuggestProjectileVelocity
        (
            this, // GameplayStatic needs context
            LaunchVelocity, // OUT parameter
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0, // TODO remove parameters from here
            0,
         ESuggestProjVelocityTraceOption::DoNotTrace
            )
        )
    {
        DesiredAimDirection = LaunchVelocity.GetSafeNormal();
        MoveBarrel();
    }
    // If can't find solution don't aim
}

/* Code that causes rotation in the WRONG direction sometimes...
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimRequest.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;
*/
/*
	Derivation of matrix multipication...
	B = BarrelRotation,  A = AimRequest,  D = Delta

	BarrelRotation rotated by some Delta gives the AimRequest direction...
	B		D =			A
	B^-1 B	D = B^-1	A
	D = B^-1	A

	B^-1 B is the identity matrix as rotations are always invertible
*/
void UTankAimingComponent::MoveBarrel()
{
	auto CurrentAim = DesiredAimDirection.ToOrientationQuat();
	
	if (!Barrel || !Turret) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().ToOrientationQuat();

	auto Delta = BarrelRotation.Inverse() * CurrentAim;
	auto DeltaRotation = Delta.Rotator();

	auto YawThrow = FMath::Clamp<float>(DeltaRotation.Yaw, -1, 1);
	Turret->Rotate(YawThrow);
	
	auto PitchThrow = FMath::Clamp<float>(DeltaRotation.Pitch, -1, 1);
	Barrel->Elevate(PitchThrow);
}
