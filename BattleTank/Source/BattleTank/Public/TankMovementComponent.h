// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeftThrottleRequest, float, Throttle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRightThrottleRequest, float, Throttle);

// Responsible for aggregating input for player (FBW and manual), and from the AI
// Maps these inputs to left and right track throttle values
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// Part of the AI movement stack, overriding to force AI to use our movement API
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

	// Takes the controller input from the player or AI from -1 to +1
	UFUNCTION(BlueprintCallable, Category=Input)
	void IntendMoveForward(float Throw);
	
	// Takes the controller input from the player or AI from -1 to +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	// Used for manual control of track throttle
	UFUNCTION(BlueprintCallable, Category = Input)
	void DriveLeftTrack(float Throttle);

	// Used for manual control of track throttle
	UFUNCTION(BlueprintCallable, Category = Input)
	void DriveRightTrack(float Throttle);

	// Delegates throttle action to TankMotor component
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnLeftThrottleRequest OnLeftThrottleRequest;

	// Delegates throttle action to TankMotor component
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnRightThrottleRequest OnRightThrottleRequest;

private:
	// Sets default values for this component's properties
	UTankMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// State kept here as this is where we aggregrate calls from various sources
	float LeftTrackThrottle = 0;
	float RightTrackThrottle = 0;
};
