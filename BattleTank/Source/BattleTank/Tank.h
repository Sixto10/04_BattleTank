// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

// Import required components
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"

#include "Tank.generated.h" // Must be the last include

// Represents the physical tank, and allows tank-level interaction such as reloading
UCLASS()
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
	const int GetRoundsLeft();

	// For forwarding to relevant component
	UFUNCTION(BlueprintCallable, Category = Control)
	void SetAimIntention(FVector WorldSpaceAim);
	
	UFUNCTION(BlueprintPure, Category = GamePlay)
	const float GetHealth();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	
	bool Aiming();

	void Fire();

protected:
	// Store required movement component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr; 
	
	// Store required movement component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category=Weapons)
	int MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category=Weapons)
	int CurrentAmmo = 0;

	float Health = 1.0;

	void BlowUpTank();
};
