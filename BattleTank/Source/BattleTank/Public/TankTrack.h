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
    // Sets a thorttle between -1 and +1
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);
	
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxTankSpeed = 400; // Set to fun speed, should be above zero

    // Max force per Track, in Newtons 
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float TrackMaxDrivingForce = 400000.f; // Assume 40 tonne tank, and 1g accelleration
	
};
