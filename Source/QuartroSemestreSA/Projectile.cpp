// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "User.h"
#include "Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	RootComponent = Sprite;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	CollisionComp->SetRelativeScale3D(FVector(0.2f, 0.5f, 0.2f));
	CollisionComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UPaperSprite> LoadedSprite(TEXT("PaperSprite'/Game/Sprites/fire_Sprite.fire_Sprite'"));
	if (LoadedSprite.Succeeded()) { Sprite->SetSprite(LoadedSprite.Object); }

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 400.0f;
	ProjectileMovement->MaxSpeed = 400.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 4.0f;

	Dano = 1;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr) {
		if (!OtherActor->IsA(AProjectile::StaticClass()) && !OtherActor->IsA(AUser::StaticClass())) {
			if (OtherActor->IsA(AEnemy::StaticClass())) {
				AEnemy* Enemy = Cast<AEnemy>(OtherActor);
				Enemy->SetLife(Enemy->GetLife() - Dano);
				UE_LOG(LogTemp, Warning, TEXT("Life: %d"), Enemy->GetLife());
			}
			Destroy();
		}
	}
}