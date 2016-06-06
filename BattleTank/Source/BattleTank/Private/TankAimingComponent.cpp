// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::Fire()
{
	if (ProjectileBlueprint)
	{
		auto Socket = FName("Projectile");
		if (!Barrel) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(Socket), Barrel->GetSocketRotation(Socket));
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!Barrel) { return false; } // Barrel may not be attached to tank yet
	auto BarrelForward = Barrel->GetForwardVector();
	return !DesiredAimDirection.Equals(BarrelForward, 0.01);
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	UpdateAim();
}

void UTankAimingComponent::AimAt(FVector WorldSpaceTarget)
{
	FVector LaunchVelocity;
	if (GetRequiredLaunchDirection(WorldSpaceTarget, LaunchVelocity))
	{
		DesiredAimDirection = LaunchVelocity;
	}
	// Can't find an aim solution so do nothing
}

bool UTankAimingComponent::GetRequiredLaunchDirection(FVector WorldSpaceTarget, FVector& LaunchVelocity)
{
	if (!Barrel) { return false; }
	FVector StartLocation = Barrel->GetComponentLocation();
	bool bIsCalculationSuccessful = UGameplayStatics::SuggestProjectileVelocity(
		this, // GameplayStatic needs context 
		LaunchVelocity, // OUT parameter
		StartLocation,
		WorldSpaceTarget,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	LaunchVelocity = LaunchVelocity.GetSafeNormal();
	return bIsCalculationSuccessful;
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
void UTankAimingComponent::UpdateAim()
{
	auto CurrentAim = DesiredAimDirection.ToOrientationQuat();
	
	if (!Barrel) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().ToOrientationQuat();

	auto Delta = BarrelRotation.Inverse() * CurrentAim;
	auto DeltaRotation = Delta.Rotator();

	RotateTurret(DeltaRotation.Yaw);

	ElevateBarrel(DeltaRotation.Pitch);
}

void UTankAimingComponent::RotateTurret(float Speed)
{
	Turret->Rotate(FMath::Clamp<float>(Speed, -1, 1));
}

void UTankAimingComponent::ElevateBarrel(float Speed)
{
	Barrel->Elevate(FMath::Clamp<float>(Speed, -1, 1));
}
