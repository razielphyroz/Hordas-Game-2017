#include "PowerUpLife.h"
#include "PaperSpriteComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "User.h"

APowerUpLife::APowerUpLife()
{
	PrimaryActorTick.bCanEverTick = true;

	Heal = FMath::FRandRange(50, 100);
}

void APowerUpLife::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AUser::StaticClass())) {
		AUser* Personagem = Cast<AUser>(OtherActor);
		Personagem->SetLife(Personagem->GetLife() + Heal);
		Destroy();
	}
}