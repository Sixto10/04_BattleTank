// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pointers not protected as in constructor, unlikely to fail
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aim Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ATank::AddAmmo(int Rounds)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Rounds, 0, MaxAmmo);
}

const int ATank::GetRoundsLeft()
{
	return CurrentAmmo;
}

void ATank::SetAimIntention(FVector WorldSpaceAim)
{
	TankAimingComponent->SetAimIntention(WorldSpaceAim); // Delegate to tank
}

const float ATank::GetHealth()
{
	return Health;
}
