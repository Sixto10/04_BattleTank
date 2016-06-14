// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Fire projectile in the direction it's currently facing
	void LaunchProjectile(float Speed);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Launch"))
	void BroadcastBPLaunchEvent();

	// Event is still referencecd by the method name, so can't rename without breaking link
	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Explode"))
	void BroadcastBPExplodeEvent();

private:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handles explosion logic, could be in BP
	void ExplodeProjectile();

	void SetDestroyTimer();

	UFUNCTION() // Required so that OnHit can be bound at runtime presumably
	void OnHit(AActor* SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnDestroyTimerExpired();
	
	UPROPERTY(VisibleAnywhere) // Pointer is visible, properties can be edited
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionForce = nullptr;

	// Not visible because we don't want to be able to edit properties in BP
	UProjectileMovementComponent *ProjectileMovement = nullptr;

	// To allow impact animation to fully play-out
	UPROPERTY(EditAnywhere)
	float DestroyDelay = 10;

	UPROPERTY(EditAnywhere)
	int32 ProjectileDamage = 20;
};
