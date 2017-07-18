// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(ensure(PlayerTank))
    {
        auto* PawnTank = Cast<ATank>(GetPawn());
        // move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
        if (ensure(AimingComponent))
        // Aim toward the player
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
        AimingComponent->Fire(); // TODO limit firing rate
    }
   
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

