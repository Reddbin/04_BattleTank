// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UTankTrack();

    virtual void BeginPlay() override;

    void ApplySidewaysForce();

    // Sets a thorttle between -1 and +1
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

	
    UPROPERTY(EditDefaultsOnly, Category = "Setup" )
    float MaxTankSpeed = 400; // Set to fun speed, should be above zero

    // Max force per Track, in Newtons 
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float TrackMaxDrivingForce = 400000.f; // Assume 40 tonne tank, and 1g accelleration

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    void DriveTrack();

    // If this is not high enough, rotating is next to impossible
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxThrottle = 1.5f;

    float CurrentThrottle = 0;
};
