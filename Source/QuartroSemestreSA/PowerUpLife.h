// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUP.h"
#include "PowerUpLife.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API APowerUpLife : public APowerUP
{
	GENERATED_BODY()
	
public:	

	APowerUpLife();

private:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
		int Heal;
	
};
