#include "QuartroSemestreSAGameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void AQuartroSemestreSAGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
		if (Controller != nullptr) {
			Controller->bShowMouseCursor = true;
		}
	}
}
