// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurretRotateRequest, float, Speed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBarrelElevateRequest, float, Speed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Tries to move barrel to position that would hit target
	void AimAt(FVector WorldSpaceTarget, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* Barrel);

	void SetTurretReference(UTankTurret* Turret);

	bool IsBarrelMoving() const;

private:
	UTankAimingComponent();

    void MoveBarrel();
    
    FVector DesiredAimDirection;
    
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
