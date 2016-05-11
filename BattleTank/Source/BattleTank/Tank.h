// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TankMovementComponent.h" // As is a required component
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
	void SetAimIntention(FVector WorldSpaceAim);

protected:
	// Store required movement component
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr; // TODO consider making this into a pure getter

private:
	UPROPERTY(EditAnywhere, Category=Weapons)
	int MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category=Weapons)
	int CurrentAmmo = 0;
};
