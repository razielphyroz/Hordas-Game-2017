#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectile();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:

	//--------------------- Métodos ---------------------//

	void DoExplosionEffect();

	void CheckDestruction();

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//-------------------- Atributos --------------------//

	bool CanDestroy;

	UPROPERTY(EditAnywhere)
		bool KeepRotationWhenExplode;

	UPROPERTY(EditAnywhere)
		int16 Dano;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* ExplosionFlipbook;
};
