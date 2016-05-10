// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMotor.h"


// Sets default values for this component's properties
UTankMotor::UTankMotor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankMotor::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankMotor::OnHit);
	
}


// Called every frame
void UTankMotor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (HitThisFrame)
	{
		HitThisFrame = false;
		IsGrounded = true;
	}
	else
	{
		IsGrounded = false;
	}
}




void UTankMotor::SetThrottle(float ThrottleRequest)
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

void UTankMotor::OnHit(AActor * SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	HitThisFrame = true;
}
