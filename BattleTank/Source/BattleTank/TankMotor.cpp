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

	// ...
	
}


// Called every frame
void UTankMotor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	auto Forward = GetOwner()->GetActorForwardVector();
	auto Force = Forward * Throttle * TrackMaxDrivingForce;
	auto OurLocation = GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *OurLocation.ToString());
	GetOwner()->GetRootPrimitiveComponent()->AddForceAtLocation(Force, OurLocation);
	Throttle = 0;
}

void UTankMotor::SetThrottle(float Throttle)
{
	this->Throttle = Throttle;
}

