// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
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
    
    // if aim or locked
    if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
    {
        AimingComponent->Fire();
    }
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) {return;}

        // TODO Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
    }
}

void ATankAIController::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("AI Tank destroyed!"))
}
