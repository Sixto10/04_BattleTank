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

// Starts the FBW system slewing towards aim point
void UTankAimingComponent::SetAimIntention(FVector WorldSpaceAim)
{
	AimRequest = WorldSpaceAim;
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

void UTankAimingComponent::UpdateAim()
{
	if (!Barrel) {
		return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimRequest.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;
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
