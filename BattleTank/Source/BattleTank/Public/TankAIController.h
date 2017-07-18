
#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    // how close can the AI tank get
    float AcceptanceRadius = 300.f;

    virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
