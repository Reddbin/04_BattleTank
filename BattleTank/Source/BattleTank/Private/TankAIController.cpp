// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));
	auto TankPawn = GetControlledTank();
	FString Message = "none";
	if (TankPawn != nullptr) {
		Message = TankPawn->GetFName().ToString();
	}
	UE_LOG(LogTemp, Warning, TEXT("AI taking control of tank: %s"), *Message);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

