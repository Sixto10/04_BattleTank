// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurretRotateRequest, float, Speed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBarrelElevateRequest, float, Speed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Tries to move barrel to position that would hit target
	void AimAt(FVector WorldSpaceAim);

	void SetBarrelReference(UTankBarrel* Barrel);

	void SetTurretReference(UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Dynamics)
	void Fire();

	bool IsBarrelMoving() const;

private:
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateAim();
		
	FVector DesiredAimDirection = FVector::ZeroVector;

	void RotateTurret(float Speed);
	void ElevateBarrel(float Speed);

	bool GetRequiredLaunchDirection(FVector WorldSpaceTarget, FVector& LaunchVelocity);

	// How fast can a projectile be launched
	UPROPERTY(EditAnywhere, Category = Dynamics)
	float LaunchSpeed = 100000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
