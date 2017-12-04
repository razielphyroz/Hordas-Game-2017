#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "User.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AUser : public APaperCharacter
{
	GENERATED_BODY()

	AUser();

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	int GetLife();
	void SetLife(int Value);

	int GetAmmoEnergy();
	void SetAmmoEnergy(int Value);

	int GetAmmoLaser();
	void SetAmmoLaser(int Value);

	void ChangeShot(int Value);

protected:

//--------------------- Métodos ---------------------//

	void MoveLeftRight(float Value);
	void MoveUpDown(float Value);
	void Move();


	UFUNCTION(BlueprintCallable)
		TSubclassOf<class AUserProjectile> ShotType();

	UFUNCTION(BlueprintCallable)
		void CheckAmmo();

//-------------------- Atributos --------------------//

	float VelX;
	float VelY;
	class UPaperFlipbook* FlipbookAtual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int AmmoLaser;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int AmmoEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		class AManagerClass* Manager;

	UPROPERTY(EditAnywhere, Category = "Atributos")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Atributos")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Atributos")
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		TArray<class UPaperFlipbook*> FlipbooksArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		TArray<TSubclassOf<class AUserProjectile>> ProjectilesArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int PosToAcessArray;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> MyScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		class UUserWidget* UserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
		int InitialLife;


};
