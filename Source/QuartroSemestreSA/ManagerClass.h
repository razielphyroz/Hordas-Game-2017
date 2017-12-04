#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManagerClass.generated.h"

UCLASS()
class QUARTROSEMESTRESA_API AManagerClass : public AActor
{
	GENERATED_BODY()
	
public:	

	AManagerClass();

	virtual void Tick(float DeltaTime) override;

	void IncreaseDeadEnemies();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DeadEnemies;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AEnemy>> EnemiesList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemy> Boss;

	float SpawnInterval;

	void SpawnEnemy();

	FTimerHandle EnemySpawnerCounter;


};
