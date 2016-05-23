// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category=GamePlay)
	bool IsDead = false; // TODO Red FLAG. Is just hitpoints!
};
