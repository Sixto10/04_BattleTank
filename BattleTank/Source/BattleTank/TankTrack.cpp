// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	SetNotifyRigidBodyCollision(true); // Same as "Simulation Generates Hit Events"
	// ...
}


// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	

}


// Called every frame
void UTankTrack::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (HitThisFrame)
	{
		HitThisFrame = false;
		IsGrounded = true;
		ApplySidewaysFriction(DeltaTime);
	}
	else
	{
		IsGrounded = false;
	}
}


void UTankTrack::SetThrottle(float ThrottleRequest)
{
	if (IsGrounded)
	{
		CurrentThrottle = ThrottleRequest;
		auto Forward = GetOwner()->GetActorForwardVector();
		FVector ForceApplied = Forward * CurrentThrottle * TrackMaxDrivingForce;
		auto OurLocation = GetComponentLocation();
		GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(ForceApplied, OurLocation);
	}

}

void UTankTrack::OnHit(AActor * SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	HitThisFrame = true;
}


// Applies friction force for this frame
void UTankTrack::ApplySidewaysFriction(float DeltaTime)
{
	auto TankRightVector = GetOwner()->GetActorRightVector();
	auto SlippageSpeed = Dot3(GetOwner()->GetVelocity(), TankRightVector);
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * TankRightVector;
	auto CorrectionForce = (GetOwner()->GetRootPrimitiveComponent()->GetMass() * CorrectionAcceleration) / 2;
	GetOwner()->GetRootPrimitiveComponent()->AddForce(CorrectionForce);
}
