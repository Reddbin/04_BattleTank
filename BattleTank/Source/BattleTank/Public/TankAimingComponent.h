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
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    // TODO add SetTurretReference
    void SetTurretReference(UTankTurret* TurretToSet);

    void AimAt(FVector HitLocation, float LauchSpeed);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus CurrentFiringStatus = EFiringStatus::Reloading;

private:


    UTankBarrel* Barrel = nullptr;

    UTankTurret* Turret = nullptr;

    void MoveBarrelTowards(FVector AimDirection);
    void MoveTurretTowards(FVector AimDirection);
	
};
