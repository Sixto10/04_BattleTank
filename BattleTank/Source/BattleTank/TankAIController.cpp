// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Consider storing if slow
	MoveToActor(Player, AcceptanceRadius);
	AimAtPlayer();
	auto ControlledTank = Cast<ATank>(GetControlledPawn());
	if (!HasFired && !ControlledTank->Aiming())
	{
		HasFired = true;
		ControlledTank->Fire();
	}
}

void ATankAIController::AimAtPlayer()
{
	auto PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	auto ControlledTank = Cast<ATank>(GetControlledPawn());

	if (ControlledTank)
	{
		ControlledTank->SetAimIntention(PlayerLocation);
	}
}