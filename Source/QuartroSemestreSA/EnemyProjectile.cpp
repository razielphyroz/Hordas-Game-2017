#include "EnemyProjectile.h"
#include "Enemy.h"
#include "PowerUP.h"
#include "User.h"

void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr) {
		if (!OtherActor->IsA(AProjectile::StaticClass()) && !OtherActor->IsA(AEnemy::StaticClass()) && !OtherActor->IsA(APowerUP::StaticClass())) {
			if (OtherActor->IsA(AUser::StaticClass())) {
				AUser* Personagem = Cast<AUser>(OtherActor);
				Personagem->SetLife(Personagem->GetLife() - Dano);
			}
			DoExplosionEffect();
		}
	}
}