// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"

#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

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

	GetOwner()->GetRootPrimitiveComponent()->AddForce(TestParam3 *  GetOwner()->GetActorRightVector() * -Dot3(GetOwner()->GetActorRightVector(), GetOwner()->GetVelocity()));
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	auto TankForward = GetOwner()->GetActorForwardVector();

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(Dot3(AIForwardIntention, TankForward));

	auto AITurnIntention = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	FString StringToPrint = FString::SanitizeFloat(AITurnIntention);
	IntendTurnRight(AITurnIntention);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

//	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Forward * Throw * DrivingForce, LeftTrackLocation);
	// GetOwner()->SetActorLocation(PreviousLocation + Forward * Throw * MaxSpeed);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	GetOwner()->GetRootPrimitiveComponent()->AddTorque(FVector(0, 0, Throw * TestParam2));
	// GetOwner()->AddActorLocalRotation(FRotator(0, Throw, 0));
}

void UTankMovementComponent::DriveLeftTrack(float Throttle)
{
	auto Forward = GetOwner()->GetActorForwardVector();
	auto ActorLocation = GetOwner()->GetActorLocation();
	auto TrackOffset = FVector(500, -250, 0);
	auto LeftTrackLocation = ActorLocation + GetOwner()->GetActorRotation().RotateVector(TrackOffset);
	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Forward * Throttle * TestParam1, LeftTrackLocation);
}

void UTankMovementComponent::DriveRightTrack(float Throttle)
{
	auto Forward = GetOwner()->GetActorForwardVector();
	auto ActorLocation = GetOwner()->GetActorLocation();
	auto TrackOffset = FVector(500, 250, 0);
	auto LeftTrackLocation = ActorLocation + GetOwner()->GetActorRotation().RotateVector(TrackOffset);
	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Forward * Throttle * TestParam1, LeftTrackLocation);
}