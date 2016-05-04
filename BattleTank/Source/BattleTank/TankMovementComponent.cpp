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

	// ...
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	auto TankForward = GetOwner()->GetActorForwardVector();

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(Dot3(AIForwardIntention, TankForward));

	auto AITurnIntention = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	FString StringToPrint = FString::SanitizeFloat(AITurnIntention);
	// PRINT(StringToPrint);
	IntendTurnRight(AITurnIntention);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Forward = GetOwner()->GetActorForwardVector();
	auto PreviousLocation = GetOwner()->GetActorLocation();
	GetOwner()->SetActorLocation(PreviousLocation + Forward * Throw * MaxSpeed);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	GetOwner()->AddActorLocalRotation(FRotator(0, Throw, 0));
}