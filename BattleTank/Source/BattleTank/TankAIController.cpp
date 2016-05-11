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
}

void ATankAIController::AimAtPlayer()
{
	auto PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	auto ControlledTank = Cast<ATank>(GetControlledPawn());

	if (ControlledTank)
	{
		auto AimIntention = PlayerLocation - ControlledTank->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Aim direction: %s"), *AimIntention.ToString())
		ControlledTank->SetAimIntention(AimIntention);
	}
}