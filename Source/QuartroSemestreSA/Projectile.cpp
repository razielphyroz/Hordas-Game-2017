#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->bGenerateOverlapEvents = false;
	Sprite->SetupAttachment(RootComponent);

	ExplosionFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	ExplosionFlipbook->SetCollisionProfileName("NoCollision");
	ExplosionFlipbook->bGenerateOverlapEvents = false;
	ExplosionFlipbook->SetLooping(false);
	ExplosionFlipbook->SetHiddenInGame(true);
	ExplosionFlipbook->Stop();
	ExplosionFlipbook->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 400.0f;
	ProjectileMovement->MaxSpeed = 400.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 4.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDestruction();
}

void AProjectile::DoExplosionEffect()
{
	InitialLifeSpan = 0.0f;
	Sprite->SetHiddenInGame(true);
	ProjectileMovement->StopMovementImmediately();
	CollisionComp->SetCollisionProfileName("NoCollision");
	if (!KeepRotationWhenExplode) {
		ExplosionFlipbook->SetWorldRotation(FRotator(0.0f, 0.0f, -90.0f));
	}
	ExplosionFlipbook->SetHiddenInGame(false);
	ExplosionFlipbook->Play();
	CanDestroy = true;
}

void AProjectile::CheckDestruction()
{
	if (!ExplosionFlipbook->IsPlaying() && CanDestroy) {
		Destroy();
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("OverlapBegin Called By Projectile.cpp"));
		Destroy();
	}
}