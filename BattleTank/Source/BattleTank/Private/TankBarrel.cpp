// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto ClampedNewElevation = FMath::Clamp<float>( RelativeRotation.Pitch + ElevationChange, MinDegreesElevation, MaxDegreesElevation);
    
    SetRelativeRotation(FRotator(ClampedNewElevation, 0, 0));
}

// Spawns a projectile at socketlocation, should be overriden by subclasses
void UTankBarrel::SpawnProjectileWithSpeed(float LaunchSpeed)
{
    if (!ensure(ProjectileBlueprint)) { return; }
    auto SpawnLocation = GetSocketLocation(FName("Projectile"));
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                          SpawnLocation,
                                                          GetSocketRotation(FName("Projectile")));
    Projectile->LaunchProjectile(LaunchSpeed);
}
