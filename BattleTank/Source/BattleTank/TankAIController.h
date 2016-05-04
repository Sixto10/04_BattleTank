// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UBlackboardData* BlackboardData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FName BlackboardPlayerPosKey = FName("PlayerPos");
};
