// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUP.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API APowerUP : public AActor
{
	GENERATED_BODY()
	
public:	

	APowerUP();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* MyFlipbook;

	UPROPERTY(EditAnywhere)
		class USphereComponent* CollisionComp;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
