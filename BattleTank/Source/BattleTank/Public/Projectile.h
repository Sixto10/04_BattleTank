// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LaunchProjectile(float Speed);
	void ExplodeProjectile();

	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Launch"))
	void BroadcastBPLaunchEvent();

	// Event is still referencecd by the method name, so can't rename without breaking link
	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Explode"))
	void BroadcastBPExplodeEvent();

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnDestroyTimerExpired();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent *ExplosionForce = nullptr;

	UProjectileMovementComponent *ProjectileMovement = nullptr;

	// To allow impact animation to fully play-out
	UPROPERTY(EditAnywhere)
	float DestroyDelay = 10;

	UPROPERTY(EditAnywhere)
	int ProjectileDamage = 20;
};
