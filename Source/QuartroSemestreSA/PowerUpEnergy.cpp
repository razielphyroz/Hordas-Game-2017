#include "PowerUpEnergy.h"
#include "User.h"

void APowerUpEnergy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AUser::StaticClass())) {
		AUser* Personagem = Cast<AUser>(OtherActor);
		Personagem->SetAmmoEnergy(Personagem->GetAmmoEnergy() + FMath::RandRange(25, 50));
		Personagem->ChangeShot(2);
		Destroy();
	}
}