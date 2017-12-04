#include "ManagerClass.h"
#include "Enemy.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/World.h"

AManagerClass::AManagerClass()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnInterval = 4.0f;
}

void AManagerClass::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}

void AManagerClass::SpawnEnemy()
{
	UWorld* World = GetWorld();

	if (World) {

		int16 RandomEnemyOne = FMath::FRandRange(0, 50);

		FActorSpawnParameters SpawnParameters;
		FVector Location(FMath::FRandRange(-350.0f, 230.0f), FMath::FRandRange(-120.0f, 560.0f), 260.0f);

		if (RandomEnemyOne == 0) {
			World->SpawnActor<AEnemy>(Boss, Location, FRotator::ZeroRotator, SpawnParameters);
		} else {
			int16 RandomEnemy = FMath::FRandRange(0, EnemiesList.Num());
			World->SpawnActor<AEnemy>(EnemiesList[RandomEnemy], Location, FRotator::ZeroRotator, SpawnParameters);
		}

		GetWorldTimerManager().SetTimer(EnemySpawnerCounter, this, &AManagerClass::SpawnEnemy, SpawnInterval, false);

		if (SpawnInterval > 1.0f) {
			SpawnInterval -= 0.2f;
		}
	}
}

void AManagerClass::IncreaseDeadEnemies()
{
	DeadEnemies++;
	if (DeadEnemies == 100 || DeadEnemies == 150 || DeadEnemies == 200 || DeadEnemies == 250) {
		SpawnInterval -= 0.2f;
	}
}

void AManagerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}