// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));
	auto PlayerTank = GetPlayerTank();
	FString Message = "none";
	if (PlayerTank != nullptr) {
		Message = PlayerTank->GetFName().ToString();
	}
	UE_LOG(LogTemp, Warning, TEXT("Found player controlled tank: %s"), *Message);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn); // no check for null needed, since Cast would simply return null if PlayerPawn were null

}
