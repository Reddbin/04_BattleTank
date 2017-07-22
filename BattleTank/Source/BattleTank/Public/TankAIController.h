// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
    // how close can the AI tank get
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 6000.f;
	
private:
    virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
