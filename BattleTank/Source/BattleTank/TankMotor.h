// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankMotor.generated.h"

// Represent the tank engine and tracks
// Responsible for translating throttle values into track forces
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMotor : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankMotor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	
	UFUNCTION()
	void OnHit(AActor* SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float TrackMaxDrivingForce = 50000;

	// Current throttle level, regardles of in air or on ground
	UPROPERTY(VisibleAnywhere)
	float CurrentThrottle = 0;

	// Is this track on the ground?
	UPROPERTY(VisibleAnywhere)
	bool IsGrounded = false; // TODO default to false later

	bool HitThisFrame = false;

	void ApplySidewaysFriction(float DeltaTime);
};
