// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

const bool ATankAIController::GetPlayerPawn(ATank** outTank)
{
	auto PlayerPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn();
	if (!PlayerPawn)
	{
		return false;
	}
	*outTank = Cast<ATank>(PlayerPawn);
	return true;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* Player;
	if (GetPlayerPawn(&Player))
	{
		MoveToActor(Player, AcceptanceRadius);
		AimAtPlayer(Player);
		auto ControlledTank = Cast<ATank>(GetControlledPawn());
		auto TimeSinceLastFire = FPlatformTime::Seconds() - LastFireTime;
		if (TimeSinceLastFire > FiringRate && !ControlledTank->Aiming())
		{
			LastFireTime = FPlatformTime::Seconds();
			ControlledTank->Fire();
		}
	}
}

void ATankAIController::AimAtPlayer(ATank* Player)
{
	auto PlayerLocation = Player->GetActorLocation();
	auto ControlledTank = Cast<ATank>(GetControlledPawn());
	if (ControlledTank)
	{
		ControlledTank->SetAimIntention(PlayerLocation);
	}
}