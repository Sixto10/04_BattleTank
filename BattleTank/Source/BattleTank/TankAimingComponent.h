// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurretRotateRequest, float, Speed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBarrelElevateRequest, float, Speed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Delegates turret rotation to turret motors
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnTurretRotateRequest OnTurretRotateRequest;

	// Delegates barrel elevation to barrel motors
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnBarrelElevateRequest OnBarrelElevateRequest;

	// For manual control
	UFUNCTION(BlueprintCallable, Category = Input)
	void RotateTurret(float Speed);

	// For manual control
	UFUNCTION(BlueprintCallable, Category = Input)
	void ElevateBarrel(float Speed);

	// For FBW control
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetAimIntention(FVector WorldSpaceAim);

	// Takes barrel reference
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(USceneComponent* BarrelInBP); // As all it needs is a transform

private:
	// State kept here as this is where we aggregrate calls from various sources
	float RotateSpeed = 0;
	float ElevateSpeed = 0;

	USceneComponent* Barrel = nullptr;
};
