// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

	
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	auto TankPawn = GetControlledTank();
	FString Message = "none";
	if (TankPawn != nullptr) {
		Message = TankPawn->GetFName().ToString();
	}
	UE_LOG(LogTemp, Warning, TEXT("Name of pawn is %s"), *Message);
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
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		
		// TODO Tell controlled tank to aim at this point
	}
	
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	// RayCast through the dot into landscapes
	// If we hit something 
		// Save the Location of the hit in OutHitLocation
		// return true;
	// Otherwise
	return true;
}
