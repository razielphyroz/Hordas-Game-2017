#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QuartroSemestreSAGameModeBase.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AQuartroSemestreSAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;
};
