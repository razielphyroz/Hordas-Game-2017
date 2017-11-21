#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
