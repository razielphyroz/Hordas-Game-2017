// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	MyFlipbook->SetCollisionProfileName("OverlapAllDynamic");
	MyFlipbook->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	//Sprite->SetRelativeScale3D(FVector(1.0f, 10.0f, 1.0f));
	RootComponent = MyFlipbook;

	Life = 5;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetLife(int16 NewLife)
{
	Life = NewLife;
	if (Life <= 0) {
		Destroy();
	}
}

int16 AEnemy::GetLife()
{
	return Life;
}