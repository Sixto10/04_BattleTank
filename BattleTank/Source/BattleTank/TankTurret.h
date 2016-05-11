// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(/*
	   */	ClassGroup = (Custom),/*
	   */	meta = (BlueprintSpawnableComponent),/*
	   */	hidecategories = ("Collision")/*
	   */)
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void Rotate(float Speed);

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20;
};
