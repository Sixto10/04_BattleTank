// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "TankMovementComponent.h"

#define OUT

// Sets default values for this component's properties
UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UTankMovementComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Pass through manual throttle requests
	OnLeftThrottleRequest.Broadcast(LeftTrackThrottle);
	OnRightThrottleRequest.Broadcast(RightTrackThrottle);

	// TODO can we remove this and let the throttle position hold state
	LeftTrackThrottle = 0;
	RightTrackThrottle = 0;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector();
	
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // Makes into a unit vector without mutating
	IntendMoveForward(Dot3(AIForwardIntention, TankForward)); // 

	//  
	auto AITurnIntention = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(AITurnIntention);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	DriveLeftTrack(Throw);
	DriveRightTrack(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	DriveLeftTrack(+Throw);
	DriveRightTrack(-Throw);
}

void UTankMovementComponent::DriveLeftTrack(float Throttle)
{
	// Note generic type specifier here
	LeftTrackThrottle = FMath::Clamp<float>(LeftTrackThrottle + Throttle, -1, 1);
}

void UTankMovementComponent::DriveRightTrack(float Throttle)
{
	RightTrackThrottle = FMath::Clamp<float>(RightTrackThrottle + Throttle, -1, 1);
}
