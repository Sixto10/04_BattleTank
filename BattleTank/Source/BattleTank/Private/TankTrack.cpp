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

    // TODO replace
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// Called every frame
void UTankTrack::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	HasTraction = HitThisFrame;
	if (HitThisFrame)
	{
		HitThisFrame = false; //Assume not hit for next frame.
		ApplySidewaysFriction(DeltaTime);
	}
}

UPrimitiveComponent* UTankTrack::GetTankRoot() const
{
	return Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::SetThrottle(float ThrottleRequest)
{
	if (HasTraction)
	{
		auto Forward = GetForwardVector();
		FVector ForceApplied = Forward * ThrottleRequest * TrackMaxDrivingForce;
		auto OurLocation = GetComponentLocation();
		GetTankRoot()->AddForceAtLocation(ForceApplied, OurLocation);
	}

}

void UTankTrack::OnHit(AActor * SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	HitThisFrame = true;
}

// Applies friction force for this frame
void UTankTrack::ApplySidewaysFriction(float DeltaTime)
{
	auto TankRightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), TankRightVector);
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * TankRightVector;
	// Now apply half the total required accelleration as we have two tracks, dodgy
	auto CorrectionForce = (GetTankRoot()->GetMass() * CorrectionAcceleration) / 2;
	GetTankRoot()->AddForce(CorrectionForce);
}
