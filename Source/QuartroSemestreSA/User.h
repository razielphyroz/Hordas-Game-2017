// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "User.generated.h"

/**
 * 
 */
UCLASS()
class QUARTROSEMESTRESA_API AUser : public APaperCharacter
{
	GENERATED_BODY()
	AUser();


public:

//--------------------- Métodos ---------------------//

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:

//--------------------- Métodos ---------------------//

	void MoveLeftRight(float Value);
	void MoveUpDown(float Value);

//-------------------- Atributos --------------------//

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* Idle;
	
	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;
};
