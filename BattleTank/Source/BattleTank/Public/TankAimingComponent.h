// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// TODO move firing here
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:
	UTankAimingComponent(); // Private OK because of Unreal magic

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveAimTowards(FVector AimDirection);

};
