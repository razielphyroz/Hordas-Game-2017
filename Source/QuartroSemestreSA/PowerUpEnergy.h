#pragma once

#include "CoreMinimal.h"
#include "PowerUP.h"
#include "PowerUpEnergy.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API APowerUpEnergy : public APowerUP
{
	GENERATED_BODY()
	
private:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
