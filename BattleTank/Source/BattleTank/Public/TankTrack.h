// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

// We are hiding categories to keep things simple in the Details tab
// Note use of comments to remove newline characters from macro
UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent)) 

// Represent the tank engine and tracks
// Responsible for translating throttle values into track forces
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPrimitiveComponent* GetTankRoot() const;

	void ApplySidewaysFriction(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float TrackMaxDrivingForce = 50000000;

	// Is this track on the ground?
	UPROPERTY(VisibleAnywhere)
	bool HasTraction = false;

	bool HitThisFrame = false;
};
