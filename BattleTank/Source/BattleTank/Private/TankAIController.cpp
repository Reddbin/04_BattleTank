// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(ensure(PlayerTank))
    {
        auto* PawnTank = Cast<ATank>(GetPawn());
        // move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

        // Aim toward the player
        PawnTank->AimAt(PlayerTank->GetActorLocation());
    
        PawnTank->Fire(); // TODO limit firing rate
    }
   
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

