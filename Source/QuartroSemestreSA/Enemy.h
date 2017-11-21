#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AEnemy : public APaperCharacter
{
	GENERATED_BODY()

	AEnemy();

public:

	int16 GetLife();
	void SetLife(int16 NewLife);
	void ChangeColorWhenHit();

protected:

	//--------------------- Métodos ---------------------//

	void BackToOriginalColor();
	void DeathEvent();

	//-------------------- Atributos --------------------//


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkVel;

	UPROPERTY(EditAnywhere)
		int16 Life;

	UPROPERTY(EditAnywhere)
		FTimerHandle TimerToChangeColor;

};
