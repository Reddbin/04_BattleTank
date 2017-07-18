
#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(ensure(PlayerTank))
    {
        auto* PawnTank = GetPawn();
        // move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

        // Aim toward the player
        if(!ensure(AimingComponent)) {return;}
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
        AimingComponent->Fire();
    }
   
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

