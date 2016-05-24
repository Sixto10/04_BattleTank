// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Register as listener of OnTankDeath event so we can detach when dead
	Cast<ATank>(GetPawn())->OnTankDeath.AddDynamic(this, &ATankAIController::OnTankDeath);
}

ATank* ATankAIController::GetPlayerTank() const
{
	// GetWorld() to obey const contract
	auto PlayerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = GetPlayerTank(); // Every frame in case de-possesed
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius); // Implemented in AAIController
		AimAtPlayer(PlayerTank);
		FireIfReady();
	}
}

void ATankAIController::AimAtPlayer(ATank* Player)
{
	auto PlayerLocation = Player->GetActorLocation();
	auto PossessedTank = Cast<ATank>(GetPawn());
	if (PossessedTank)
	{
		PossessedTank->SetAimIntention(PlayerLocation);
	}
}

void ATankAIController::FireIfReady()
{
	auto PossessedTank = Cast<ATank>(GetPawn());
	auto TimeSinceLastFire = FPlatformTime::Seconds() - LastFireTime;
	bool bHasFinishedAiming = !PossessedTank->IsBarrelMoving();

	if (TimeSinceLastFire > FiringRate && bHasFinishedAiming)
	{
		LastFireTime = FPlatformTime::Seconds();
		PossessedTank->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy(); // To stop AI driving tank
}