// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class AProjectile;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downward speed, and +1 is max up speed
    void Elevate(float RelativeSpeed);

    // this is virtual to later implement composite pattern
    void SpawnProjectileWithSpeed(float LaunchSpeed);
	
private:
    // This determines which Projectile will be spawned
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category= "Setup")
    float MaxDegreesPerSecond = 10;
	
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesElevation = 40;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinDegreesElevation = 0;
};
