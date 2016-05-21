// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh); // Projectile Movement expecting this
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(RootComponent);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachTo(RootComponent);
	ImpactBlast->bAutoActivate = false;	
	
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachTo(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	OnLaunchProjectile();
}

void AProjectile::OnHit(AActor * SelfActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ExplodeProjectile();
}

void AProjectile::ExplodeProjectile()
{
	LaunchBlast->Deactivate(); //Stop the smoke trail;
	ImpactBlast->Activate(); //Make explode;
	ExplosionForce->FireImpulse(); //Force impact;

								   //Need to explicitly set so that ApplyRadialDamage always works. Otherwise seems to race with destruction of root comp.
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(), TArray<AActor *>()); //Inflict damage

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnDestroyTimerExpired, DestroyDelay, false);

	OnExplodeProjectile();
}


void AProjectile::OnDestroyTimerExpired()
{
	Destroy();
}
