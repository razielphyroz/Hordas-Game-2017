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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnHit(AActor* OtherActor);

protected:

	//--------------------- Métodos ---------------------//

	void BackToOriginalColor();
	void DeathEvent();
	void PowerUP();
	void Move();
	void UpdateDirection(FRotator Direction);
	void ChangeCanDamagePlayer();

	//-------------------- Atributos --------------------//

	TSubclassOf<AActor> LifePowerUpRef;
	TSubclassOf<AActor> AmmoLaserRef;
	TSubclassOf<AActor> AmmoEnergyRef;
	bool CanDamagePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		float WalkVel;

	UPROPERTY(EditAnywhere, Category = "Atributos")
		int16 Life;

	UPROPERTY(EditAnywhere)
		FTimerHandle TimerToChangeColor;

	UPROPERTY(EditAnywhere)
		FTimerHandle AttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int Damage;

	UPROPERTY(BlueprintReadWrite)
		class AUser* Personagem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		TArray<class UPaperFlipbook*> FlipbooksArray;

};
