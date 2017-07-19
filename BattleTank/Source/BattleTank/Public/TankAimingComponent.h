// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward Declaration
class AProjectile;
class UTankBarrel; 
class UTankTurret;

// Hold barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    UFUNCTION(BlueprintCallable)
    void Fire();

    UFUNCTION(BlueprintCallable)
    void AimAt(FVector HitLocation);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus CurrentFiringStatus = EFiringStatus::Locked;

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    void MoveBarrelTowards(FVector AimDirection);

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    double LastFireTime = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000; // Sensible starting value off 1000 m/s

};
