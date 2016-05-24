// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

// Import required components
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"

#include "Tank.generated.h" // Must be the last include

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathEvent);

// Represents the physical tank, and allows tank-level interaction such as reloading
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category=Weapons)
	void AddAmmo(int Rounds);

	UFUNCTION(BlueprintPure, Category=Weapons)
	int GetRoundsLeft() const;

	// For forwarding to relevant component
	UFUNCTION(BlueprintCallable, Category = Control)
	void SetAimIntention(FVector WorldSpaceAim);
	
	UFUNCTION(BlueprintPure, Category = GamePlay)
	float GetHealthPercent() const; // Discuss

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	
	bool IsBarrelMoving() const;

	void Fire();

	/** Broadcasts whenever the layer changes */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTankDeathEvent OnTankDeath;

protected:
	// Store required movement component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr; 
	
	// Store required movement component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category=Setup)
	int MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category= Setup)
	int CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	int StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Setup)
	int CurrentHealth = StartingHealth;

	void BlowUpTank();
};
