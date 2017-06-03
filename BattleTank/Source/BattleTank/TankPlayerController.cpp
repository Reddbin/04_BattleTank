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

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}



