// Fill out your copyright notice in the Description page of Project Settings.

#include "FatalExplosionPowerUP.h"
#include "User.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "UserProjectile.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

void AFatalExplosionPowerUP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AUser::StaticClass())) {

		UWorld* World = GetWorld();

		if (World) {

			AUser* Personagem = Cast<AUser>(OtherActor);

			TArray<AActor*> ActorsArray;
			UGameplayStatics::GetAllActorsOfClass(World, AEnemy::StaticClass(), ActorsArray);

			FActorSpawnParameters SpawnParameters;
			FVector Location = Personagem->GetActorLocation();

			for (int i = 0; i < ActorsArray.Num(); i++) {

				AEnemy* MyEnemy = Cast<AEnemy>(ActorsArray[i]);
				FRotator Direction = UKismetMathLibrary::FindLookAtRotation(Location, MyEnemy->GetActorLocation());
				Direction.Pitch = 0;
				World->SpawnActor<AUserProjectile>(FatalProjectile, Location, Direction, SpawnParameters);

				if (i >= 10) {
					break;
				}
			}
		}

		Destroy();
	}
}