// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

// Required as UBlackboardComponent is a forward declaration in AIController.h
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h" 

#include "TankAIController.h"

#define OUT

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UseBlackboard(BlackboardData, OUT Blackboard);
	RunBehaviorTree(BehaviorTree);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Blackboard->SetValueAsVector(BlackboardPlayerPosKey, Player->GetActorLocation());
}