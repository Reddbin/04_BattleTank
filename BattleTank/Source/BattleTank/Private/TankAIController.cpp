// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!ensure(PlayerTank && AimingComponent)) {return;}

    // move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
    // Aim toward the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    AimingComponent->Fire();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

