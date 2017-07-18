// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above this


// Forward Declaration#includes


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000; // Sensible starting value off 1000 m/s
};
