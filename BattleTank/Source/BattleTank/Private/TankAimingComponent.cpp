// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if(!BarrelToSet){return;}
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    if (!TurretToSet) { return; }
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed)
{
    if (!Barrel) { return;}
    if (!Turret) { return;}

    FVector OutLauchnVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                        OutLauchnVelocity,
                                                                        StartLocation,
                                                                        HitLocation,
                                                                        LauchSpeed,
                                                                        false,
                                                                        0,
                                                                        0,
                                                                        ESuggestProjVelocityTraceOption::DoNotTrace);
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLauchnVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        MoveTurretTowards(AimDirection);
    }
    
    // If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Get the difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
    // Get the difference between current turret rotation, and AimDirection
    auto TurretRotator = Turret->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - TurretRotator;

    Turret->Rotate(DeltaRotator.Yaw);
}
