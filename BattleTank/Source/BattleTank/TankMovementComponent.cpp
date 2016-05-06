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
	// Sideways force
	// GetOwner()->GetRootPrimitiveComponent()->AddForce(TestParam3 *  GetOwner()->GetActorRightVector() * -Dot3(GetOwner()->GetActorRightVector(), GetOwner()->GetVelocity()));
	auto Forward = ForwardDriver;
	ForwardDriver = FVector::ZeroVector;
	auto ActorLocation = GetOwner()->GetActorLocation();

	auto LeftTrackLocation = ActorLocation + GetOwner()->GetActorRotation().RotateVector(FVector(0, -250, 0));
	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Forward * LeftTrackThrottle * TrackMaxDrivingForce, LeftTrackLocation);
	
	auto RightTrackLocation = ActorLocation + GetOwner()->GetActorRotation().RotateVector(FVector(0, 250, 0));
	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Forward * RightTrackThrottle * TrackMaxDrivingForce, RightTrackLocation);

	LeftTrackThrottle = 0;
	RightTrackThrottle = 0;
}

FVector UTankMovementComponent::FindGroundForward()
{
	auto ProbeSpheres = GetOwner()->GetComponentsByTag(USphereComponent::StaticClass(), FName("GroundProbe"));
	if (ProbeSpheres.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find me none of them there GroundProbe tags"));
		return FVector::ZeroVector;
	}
	
	auto Sphere = Cast<USphereComponent>(ProbeSpheres[0]);
	FVector CollisionVector = FVector::ZeroVector;
	auto Distance = Sphere->GetDistanceToCollision(Sphere->GetComponentLocation(), OUT CollisionVector);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f, Vector: %s"), Distance, *CollisionVector.ToString());

	return GetOwner()->GetActorForwardVector();
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);
	// UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove"));

	auto TankForward = GetOwner()->GetActorForwardVector();

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(Dot3(AIForwardIntention, TankForward));

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
	// if intending right, suppress right throttle proporpionately

	if (Throw > 0)
	{
		RightTrackThrottle = RightTrackThrottle - Throw;
	}
	else
	{
		LeftTrackThrottle = LeftTrackThrottle + Throw;
	}
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

