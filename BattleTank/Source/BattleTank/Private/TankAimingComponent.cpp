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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
    if (isReloaded)
    {
        CurrentFiringStatus = EFiringStatus::Reloading;
    }
    else if (IsBarrelMoving())
    {
        CurrentFiringStatus = EFiringStatus::Aiming;
    }
    else
    {
        CurrentFiringStatus = EFiringStatus::Locked;
    }
    // TODO Handle aiming and locket states
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
    return CurrentFiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if(!ensure(Barrel)) {return false;}
    return !Barrel->GetForwardVector().FVector::Equals(AimDirection, 0.1f);
}

// Setting up the components
void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

// Finds the vector for hiting the target and moves turret+ barrel if there is a solution 
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
        AimDirection = OutLauchnVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

// Delegates to Barrel and Turret for purpose of moving them
void UTankAimingComponent::MoveBarrelTowards(FVector ResultNormal)
{
    // Get the difference between current barrel rotation, and AimDirection
    if (!ensure(Barrel)) { return; }
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = ResultNormal.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    // always use shortest way around
    if (FMath::Abs(DeltaRotator.Yaw) < 180.f)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

// Responsible for spawning the projectile at, if ready
void UTankAimingComponent::Fire()
{
    if (CurrentFiringStatus != EFiringStatus::Reloading)
    {
        if (!ensure(Barrel && ProjectileBlueprint)) { return; }
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

