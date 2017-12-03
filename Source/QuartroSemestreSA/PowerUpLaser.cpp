#include "PowerUpLaser.h"
#include "User.h"

void APowerUpLaser::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AUser::StaticClass())) {
		AUser* Personagem = Cast<AUser>(OtherActor);
		Personagem->SetAmmoLaser(Personagem->GetAmmoLaser() + FMath::RandRange(25, 50));
		Personagem->ChangeShot(1);
		Destroy();
	}
}