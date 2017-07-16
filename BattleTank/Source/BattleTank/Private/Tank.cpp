// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    UE_LOG(LogTemp, Warning, TEXT("DONKEY: Constructor called in c++"))
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    
}

void ATank::Fire()
{
    if (!TankAimingComponent) { return; }
    TankAimingComponent->Fire(LaunchSpeed);
}

void ATank::AimAt(FVector HitLocation)
{
    if(!TankAimingComponent) {return;}
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


