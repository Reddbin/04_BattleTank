// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

	
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
    auto* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }
}

// Tick
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick Tock"));
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation; // Out parameter
    auto* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
        if(!ensure(AimingComponent)) {return;}
        AimingComponent->AimAt(HitLocation);
		// TODO Tell controlled tank to aim at this point
	}
	
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De_project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
        // Line-trace along that look, and see what we hit (up to max range)
        FHitResult HitLocation;  // out param
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return true;
}

// Returns false if unable to determine value
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector WorldLocation;  // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
		                                  ScreenLocation.Y, 
		                                  WorldLocation, 
		                                  OutLookDirection);
}

// Line trace with single channel, returns true if something was hit
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult HitResult;
    FVector StartOfLine = PlayerCameraManager->GetCameraLocation();
    FVector EndOfLine = StartOfLine + LineTraceRange * LookDirection;
    if (GetWorld()->LineTraceSingleByChannel(HitResult,
                                             StartOfLine,
                                             EndOfLine,
                                             ECC_Visibility)
        )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    OutHitLocation = FVector(0.0);
    return false; // Line trace didn't succeed
}
