// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false; // Note tick suppression

	// Collision probe
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh); // Projectile Movement expecting this
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	// Particle effects
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(RootComponent);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachTo(RootComponent);
	ImpactBlast->bAutoActivate = false;	
	
	// To make hit tanks move
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    // TODO fix
	ExplosionForce->AttachTo(RootComponent);

	// For balistic calculations
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Listen for the collision mesh's OnHit event, delegate to OnHit
    // TODO replace
	// CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	BroadcastBPLaunchEvent();
}

// The signature of this method came from inspecting the type of OnComponentHit
void AProjectile::OnHit(AActor * SelfActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ExplodeProjectile();
}

void AProjectile::ExplodeProjectile()
{
	LaunchBlast->Deactivate(); // Stop the smoke trail
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	// Need to explicitly set so that ApplyRadialDamage always works.
	// Otherwise seems to race with destruction of root comp.
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent(); // Remove obstruction once exploded

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor *>() // Ignore no actors
	);

	SetDestroyTimer();
	BroadcastBPExplodeEvent();
}

// Gives particles effects time to finish
void AProjectile::SetDestroyTimer()
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(
		Timer,
		this,
		&AProjectile::OnDestroyTimerExpired,
		DestroyDelay,
		false
	);
}

void AProjectile::OnDestroyTimerExpired()
{
	Destroy();
}
