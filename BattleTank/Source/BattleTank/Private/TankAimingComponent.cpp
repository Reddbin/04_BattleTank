// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
    Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed)
{
    if (!Barrel) { return;}

    FVector OutLauchnVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    if (UGameplayStatics::SuggestProjectileVelocity(this,
                                                    OutLauchnVelocity,
                                                    StartLocation,
                                                    HitLocation,
                                                    LauchSpeed,
                                                    false,
                                                    0,
                                                    0,
                                                    ESuggestProjVelocityTraceOption::DoNotTrace)
        )
    {
        auto AimDirection = OutLauchnVelocity.GetSafeNormal();
        UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
    }
    // If no solution found do nothing
}

