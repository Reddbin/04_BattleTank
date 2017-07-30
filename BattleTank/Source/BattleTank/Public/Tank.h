// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above this



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100;

    // Health of this tank
    UPROPERTY(VisibleAnywhere, Category = "Setup")
    int32 CurrentHealth = StartingHealth;
};
