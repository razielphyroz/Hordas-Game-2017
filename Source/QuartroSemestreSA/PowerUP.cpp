#include "PowerUP.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

APowerUP::APowerUP()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APowerUP::OnOverlapBegin);
	RootComponent = CollisionComp;

	MyFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	MyFlipbook->SetCollisionProfileName("NoCollision");
	MyFlipbook->SetupAttachment(CollisionComp);
}

void APowerUP::BeginPlay()
{
	Super::BeginPlay();
}

void APowerUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUP::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}
