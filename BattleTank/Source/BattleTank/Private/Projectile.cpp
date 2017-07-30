// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(RootComponent,
                                   FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(RootComponent,
                                   FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;
    ImpactBlast->Deactivate();

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent,
                                      FAttachmentTransformRules::SnapToTargetIncludingScale);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
    ProjectileMovementComponent->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
    ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
    ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();

    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();

    if (UGameplayStatics::ApplyRadialDamage(this,
                                            ProjectileDamage,
                                            GetActorLocation(),
                                            ExplosionForce->Radius, // for consistency
                                            UDamageType::StaticClass(),
                                            TArray<AActor*>()       // damage all actors
    ))
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile Applied damage"));
    }

    FTimerHandle TimerHandel;
    GetWorld()->GetTimerManager().SetTimer(TimerHandel,this, &AProjectile::DestroyProjectile, DestroyDelay, false);
}

void AProjectile::DestroyProjectile()
{
    Destroy();
}
