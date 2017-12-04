// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUP.h"
#include "FatalExplosionPowerUP.generated.h"

/**
 * 
 */
UCLASS()
class QUARTROSEMESTRESA_API AFatalExplosionPowerUP : public APowerUP
{
	GENERATED_BODY()
	
	
private:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AUserProjectile> FatalProjectile;
};
