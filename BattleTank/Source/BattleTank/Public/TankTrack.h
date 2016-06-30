// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1, UFUNCTION so can be bound directly to input
	UFUNCTION(BlueprintCallable, Category = Input) // TODO maybe remove
	void SetThrottle(float Throttle);
	
private:
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g accelleration
};
