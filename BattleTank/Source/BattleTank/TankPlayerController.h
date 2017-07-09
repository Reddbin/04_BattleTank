// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;
/**
 *  
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector & OutHitLocation) const;

	// return an OUT parameter
	bool GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;
};
