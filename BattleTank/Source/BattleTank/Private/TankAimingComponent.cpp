// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// is called from BP
void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

// Looks if the target is within range and move turret+barrel to towards it
void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return;}
    if (!ensure(Turret)) { return;}

    FVector OutLauchnVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                        OutLauchnVelocity,
                                                                        StartLocation,
                                                                        HitLocation,
                                                                        LaunchSpeed,
                                                                        false,
                                                                        0,
                                                                        0,
                                                                        ESuggestProjVelocityTraceOption::DoNotTrace);
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLauchnVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

// Delegates movement of barrel and turret towards components
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Get the difference between current barrel rotation, and AimDirection
    if (!ensure(Barrel)) { return; }
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}

// Checks whether firing is ready and spawns a projecile if true
void UTankAimingComponent::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if(!ensure(Barrel)) {return;}
    if (isReloaded)
    {
        // Spawn a projectile at the socket location of the barrel
        auto SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                              SpawnLocation,
                                                              Barrel->GetSocketRotation(FName("Projectile")));

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        CurrentFiringStatus = EFiringStatus::Reloading;
    }
}

