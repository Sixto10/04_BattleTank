// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Tank.h"

#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaSeconds) override;

	void FireIfReady();

	
private:
	virtual void BeginPlay() override;

	void AimAtPlayer(ATank* Player);
	ATank* GetPlayerTank() const;

	UFUNCTION() // Just coz
	void OnTankDeath();

	UPROPERTY(EditAnywhere, Category = "AI Setup")
	float AcceptanceRadius = 5.0;

	float LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = "AI Setup")
	float FiringRate = 5;
};
