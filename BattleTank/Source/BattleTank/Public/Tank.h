// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

// Import required components
#include "TankMovementComponent.h"
#include "TankAimingComponent.h" // In turn imports barrel and turret
#include "Tank.generated.h" // Must be the last include

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathEvent);

// Represents the physical tank, and allows tank-level interaction such as reloading
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Weapons)
	void AddAmmo(int Rounds);

	UFUNCTION(BlueprintPure, Category=Weapons)
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintPure, Category = GamePlay)
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* Turret);

	bool IsBarrelMoving() const;

	// For forwarding to relevant component
	UFUNCTION(BlueprintCallable, Category = Control)
	void AimAt(FVector HitLocation);
	
	// Signature comes from engine code
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable, Category = Control)
	void Fire();
	
	UPROPERTY(BlueprintAssignable)
	FTankDeathEvent OnTankDeath;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr; 
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	ATank();
	
	UPROPERTY(EditAnywhere, Category=Setup)
	int32 MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category= Setup)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Setup)
	int32 CurrentHealth = StartingHealth;

	void BlowUpTank();

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// How fast can a projectile be launched
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;

	// How fast can a projectile be launched
	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeInSeconds = 5;

	float LastFireTime = 0;
};
