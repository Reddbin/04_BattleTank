// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // No need to protect pointers as addad at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if (Barrel && isReloaded)
    {
        // Spawn a projectile at the socket location of the barrel
        auto SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                              SpawnLocation,
                                                              Barrel->GetSocketRotation(FName("Projectile")));

        Projectile->LaunchProjectile(LauchnSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
    
    
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LauchnSpeed);
}


