// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	Cast<ATank>(GetPawn())->OnTankDeath.AddDynamic(this, &ATankAIController::OnTankDeath);
}

ATank* ATankAIController::GetPlayerTank() const
{
	// GetWorld() rather than this to obey const contract
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
		MoveToActor(PlayerTank, AcceptanceRadius); // Implimented in AAIController
		AimAtPlayer(PlayerTank);
		FireIfReady();
	}
}

void ATankAIController::AimAtPlayer(ATank* Player)
{
	auto PlayerLocation = Player->GetActorLocation();
	auto AITank = Cast<ATank>(GetControlledPawn());
	if (AITank)
	{
		AITank->SetAimIntention(PlayerLocation);
	}
}

void ATankAIController::FireIfReady()
{
	auto ControlledTank = Cast<ATank>(GetControlledPawn());
	auto TimeSinceLastFire = FPlatformTime::Seconds() - LastFireTime;
	bool bHasFinishedAiming = !ControlledTank->IsBarrelMoving();
	if (TimeSinceLastFire > FiringRate && bHasFinishedAiming)
	{
		LastFireTime = FPlatformTime::Seconds();
		ControlledTank->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy(); // To stop AI driving tank
}