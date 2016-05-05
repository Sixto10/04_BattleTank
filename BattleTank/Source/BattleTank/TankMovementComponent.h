// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/FloatingPawnMovement.h"
#include "TankMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankMovementComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

	// Takes the controller input from the player or AI from -1 to +1
	// TODO map AI movement through this layer
	UFUNCTION(BlueprintCallable, Category=Input)
	void IntendMoveForward(float Throw);
	
	// Takes the controller input from the player or AI from -1 to +1
	// TODO map AI movement through this layer
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void DriveLeftTrack(float Throttle);

	UFUNCTION(BlueprintCallable, Category = Input)
	void DriveRightTrack(float Throttle);


private:
	float MaxSpeed = 50;

	UPROPERTY(EditAnywhere)
	float TestParam1 = 0;

	UPROPERTY(EditAnywhere)
		float TestParam2 = 0;

	UPROPERTY(EditAnywhere)
	float TestParam3 = 0;


};
