// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    
	
private:
    // how close can the AI tank get
    float AcceptanceRadius = 3000.f;

    virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
