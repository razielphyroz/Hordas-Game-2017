#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "UserProjectile.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AUserProjectile : public AProjectile
{
	GENERATED_BODY()
		
protected:

	//--------------------- Métodos ---------------------//
	
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};