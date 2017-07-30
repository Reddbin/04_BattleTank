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
    Locked,
    OutOfAmmo
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
    bool AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    int32 GetCurrentAmmo() const;

    EFiringStatus GetFiringState() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus CurrentFiringStatus = EFiringStatus::Reloading;

    virtual void BeginPlay() override;

private:
    bool IsBarrelMoving() const;

    bool HasNoAmmo() const;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    void MoveBarrelTowards(FVector AimDirection);

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    // Used for checking whether firing is possible again
    double LastFireTime = 0;

    // Is determined in AimAt and used as the point to move to barrel towards
    FVector AimDirection = FVector().ZeroVector;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 8000; // Sensible starting value off 1000 m/s

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    // Will be displayed on screen
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 CurrentAmmo = 30;
};
