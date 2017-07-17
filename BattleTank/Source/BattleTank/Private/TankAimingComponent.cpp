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

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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
    //MoveBarrelTowards(HitLocation);
    //MoveTurretTowards(HitLocation); // turret should move to the cursor even without Aim solution
    // If no solution found do nothing
}

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

void UTankAimingComponent::Fire(float LaunchSpeed)
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

