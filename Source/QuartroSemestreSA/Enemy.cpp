#include "Enemy.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "User.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "PowerUpLife.h"
#include "PowerUpLaser.h"
#include "PowerUpEnergy.h"
#include "FatalExplosionPowerUP.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "ManagerClass.h"

AEnemy::AEnemy()
{
	bBlockInput = true;
	CanDamagePlayer = true;

	ConstructorHelpers::FObjectFinder<UClass>LifePowerUP(TEXT("Blueprint'/Game/Blueprints/PowerUPs/PowerUpLifeBP.PowerUpLifeBP_C'"));
	if (LifePowerUP.Succeeded()) { LifePowerUpRef = Cast<UClass>(LifePowerUP.Object);	}

	ConstructorHelpers::FObjectFinder<UClass>AmmoLaser(TEXT("Blueprint'/Game/Blueprints/PowerUPs/LaserAmmoBP.LaserAmmoBP_C'"));
	if (AmmoLaser.Succeeded()) { AmmoLaserRef = Cast<UClass>(AmmoLaser.Object); }

	ConstructorHelpers::FObjectFinder<UClass>AmmoEnergy(TEXT("Blueprint'/Game/Blueprints/PowerUPs/EnergyAmmoBP.EnergyAmmoBP_C'"));
	if (AmmoEnergy.Succeeded()) { AmmoEnergyRef = Cast<UClass>(AmmoEnergy.Object); }

	ConstructorHelpers::FObjectFinder<UClass>LoadFatal(TEXT("Blueprint'/Game/Blueprints/PowerUPs/FatalExplosionPowerUPBP.FatalExplosionPowerUPBP_C'"));
	if (LoadFatal.Succeeded()) { FatalExplosion = Cast<UClass>(LoadFatal.Object); }

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::SetLife(int16 NewLife)
{

	ChangeColorWhenHit();

	if (NewLife <= 0) {
		DeathEvent();
	} else {
		Life = NewLife;
	}
}

int16 AEnemy::GetLife()
{
	return Life;
}

void AEnemy::ChangeColorWhenHit()
{
	GetSprite()->SetSpriteColor(FLinearColor::Black);
	GetWorldTimerManager().SetTimer(TimerToChangeColor, this, &AEnemy::BackToOriginalColor, 0.1f, false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World) {
		APawn* Player = UGameplayStatics::GetPlayerPawn(World, 0);
		if (Player) {
			Personagem = Cast<AUser>(Player);
		}
		
		TArray<AActor*> ActorsArray;
		UGameplayStatics::GetAllActorsOfClass(World, AManagerClass::StaticClass(), ActorsArray);

		if (ActorsArray.Num() >= 1) {
			Manager = Cast<AManagerClass>(ActorsArray[0]);
		}
	}

	GetWorldTimerManager().SetTimer(TimeToSpawn, this, &AEnemy::StartPlay, 5.0f, false);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ReadyToPlay) {
		Move();
	}

}

void AEnemy::Move()
{
	FRotator Direction = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Personagem->GetActorLocation());
	AddMovementInput(Direction.Vector(), WalkVel);
	UpdateDirection(Direction);
}

void AEnemy::UpdateDirection(FRotator Direction)
{
	UPaperFlipbook* FlipbookAtual = GetSprite()->GetFlipbook();

	if (Direction.Yaw >= -45.0f && Direction.Yaw <= 45.0f && FlipbookAtual != FlipbooksArray[3]) {
		GetSprite()->SetFlipbook(FlipbooksArray[3]);
	} else if (Direction.Yaw < -45.0f && Direction.Yaw >= -135.0f && FlipbookAtual != FlipbooksArray[0]) {
		GetSprite()->SetFlipbook(FlipbooksArray[0]);
	} else if ((Direction.Yaw < -135.0f && Direction.Yaw >= -180.0f || Direction.Yaw <= 180.0f && Direction.Yaw >= 135.0f) && FlipbookAtual != FlipbooksArray[2]) {
		GetSprite()->SetFlipbook(FlipbooksArray[2]);
	} else if (Direction.Yaw <= 135.0f && Direction.Yaw > 45.0f && FlipbookAtual != FlipbooksArray[1]) {
		GetSprite()->SetFlipbook(FlipbooksArray[1]);
	}
}

void AEnemy::BackToOriginalColor()
{
	GetSprite()->SetSpriteColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void AEnemy::PowerUP()
{
	int16 RandomPowerUP = FMath::FRandRange(0, 2);

	if (RandomPowerUP <= 1) {

		UWorld* World = GetWorld();
		
		if (World) {
		
			FActorSpawnParameters SpawnParameters;
			FVector Location(GetActorLocation().X, GetActorLocation().Y, 225.0f);

			switch (RandomPowerUP) {
			case 0:
				World->SpawnActor<APowerUpLife>(LifePowerUpRef, Location, FRotator::ZeroRotator, SpawnParameters);
				break;
			case 1:
				int AmmoType = FMath::FRandRange(0, 11);
			
				if (AmmoType <= 4) {
					World->SpawnActor<APowerUpLaser>(AmmoLaserRef, Location, FRotator::ZeroRotator, SpawnParameters);
				} else if (AmmoType > 4 && AmmoType <= 9) {
					World->SpawnActor<APowerUpEnergy>(AmmoEnergyRef, Location, FRotator::ZeroRotator, SpawnParameters);
				} else {
					World->SpawnActor<AFatalExplosionPowerUP>(FatalExplosion, Location, FRotator::ZeroRotator, SpawnParameters);
				}
				break;
			}
		}
	}
}

void AEnemy::DeathEvent()
{
	PowerUP();
	Manager->IncreaseDeadEnemies();
	Destroy();
}

void AEnemy::ChangeCanDamagePlayer()
{
	CanDamagePlayer = true;
}

void AEnemy::StartPlay()
{
	ReadyToPlay = true;
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
}

void AEnemy::OnHit(AActor* OtherActor)
{
	if (CanDamagePlayer && OtherActor == Personagem) {
		Personagem->SetLife(Personagem->GetLife() - Damage);
		CanDamagePlayer = false;
		GetWorldTimerManager().SetTimer(AttackInterval, this, &AEnemy::ChangeCanDamagePlayer, 1.5f, false);
	}
}