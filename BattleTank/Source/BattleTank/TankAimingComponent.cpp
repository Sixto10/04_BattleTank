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

	// ...
}

void UTankAimingComponent::SetBarrelReference(USceneComponent* BarrelInBP)
{
	Barrel = BarrelInBP; // Sam thought of this, I said we should do this->Barrel = Barrel but he wouldn't listen.
}

void UTankAimingComponent::Fire()
{
	if (ProjectileBlueprint)
	{
		auto Socket = FName("Projectile");
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(Socket), Barrel->GetSocketRotation(Socket));
		Projectile->Launch(LaunchSpeed);
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UpdateAim();

	// Pass through manual turret requests
	OnTurretRotateRequest.Broadcast(RotateSpeed);
	RotateSpeed = 0;

	OnBarrelElevateRequest.Broadcast(ElevateSpeed);
	ElevateSpeed = 0;
}

// Starts the FBW system slewing towards aim point
void UTankAimingComponent::SetAimIntention(FVector WorldSpaceAim)
{
	if (!Barrel)
	{
		return;
	}
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetComponentLocation();
	if (UGameplayStatics::SuggestProjectileVelocity(GetOwner(), 
		TossVelocity, 
		StartLocation, 
		WorldSpaceAim, 
		LaunchSpeed, 
		false, 
		0, 0, 
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimRequest = TossVelocity.GetSafeNormal();
	}
}

void UTankAimingComponent::UpdateAim()
{
	if (!Barrel) {
		return;
	}
	/* Code that causes rotation in the WRONG direction sometimes...
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimRequest.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;
	*/

	auto CurrentAim = AimRequest.ToOrientationQuat();
	auto BarrelRotation = Barrel->GetForwardVector().ToOrientationQuat();

	/*
	Derivation of matrix multipication...
	B = BarrelRotation,  A = AimRequest,  D = Delta
	
	BarrelRotation rotated by some Delta gives the AimRequest direction...
	B		D =			A
	B^-1 B	D = B^-1	A
			D = B^-1	A
	
	B^-1 B is the identity matrix as rotations are always invertible
	*/
	auto Delta = BarrelRotation.Inverse() * CurrentAim;

	auto DeltaRotation = Delta.Rotator();

	RotateTurret(DeltaRotation.Yaw);
	ElevateBarrel(DeltaRotation.Pitch);
}

void UTankAimingComponent::RotateTurret(float Speed)
{
	RotateSpeed = FMath::Clamp<float>(RotateSpeed + Speed, -1, 1);
}

void UTankAimingComponent::ElevateBarrel(float Speed)
{
	ElevateSpeed = FMath::Clamp<float>(ElevateSpeed + Speed, -1, 1);
}
