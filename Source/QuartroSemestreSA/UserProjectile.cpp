#include "UserProjectile.h"
#include "User.h"
#include "Enemy.h"

void AUserProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor != nullptr) {
		if (!OtherActor->IsA(AProjectile::StaticClass()) && !OtherActor->IsA(AUser::StaticClass())) {
			if (OtherActor->IsA(AEnemy::StaticClass())) {
				AEnemy* Enemy = Cast<AEnemy>(OtherActor);
				Enemy->SetLife(Enemy->GetLife() - Dano);
			}
			DoExplosionEffect();
		}	
	}		
}