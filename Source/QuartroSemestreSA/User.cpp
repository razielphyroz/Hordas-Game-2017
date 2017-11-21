// Fill out your copyright notice in the Description page of Project Settings.

#include "User.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"

AUser::AUser()
{

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->SetupAttachment(GetSprite());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 512.0f;
	Camera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	GetCharacterMovement()->MaxWalkSpeed = 250;
}

void AUser::BeginPlay()
{ 
	Super::BeginPlay(); 

	if (MyScreen != NULL) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
			if (Controller != nullptr) {
				UserWidget = UWidgetBlueprintLibrary::Create(World, MyScreen, Controller);
				if (UserWidget != nullptr) {
					UserWidget->AddToViewport();
				}
			}
		}
	}
}

void AUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AUser::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AUser::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &AUser::MoveUpDown);
}

void AUser::MoveUpDown(float Value)
{ VelY = Value; }

void AUser::MoveLeftRight(float Value)
{ VelX = Value; }

void AUser::Move()
{
	FlipbookAtual = GetSprite()->GetFlipbook();

	if (VelX == 0 && VelY == 0) {
		if (FlipbookAtual == FlipbooksArray[4]) {
			GetSprite()->SetFlipbook(FlipbooksArray[0]);
		} else if (FlipbookAtual == FlipbooksArray[5]) {
			GetSprite()->SetFlipbook(FlipbooksArray[1]);
		} else if (FlipbookAtual == FlipbooksArray[6]) {
			GetSprite()->SetFlipbook(FlipbooksArray[2]);
		} else if (FlipbookAtual == FlipbooksArray[7]) {
			GetSprite()->SetFlipbook(FlipbooksArray[3]);
		}
	} else {
		if (FMath::Abs(VelX) >= FMath::Abs(VelY)) {
			if (VelX < 0 && FlipbookAtual != FlipbooksArray[6]) {
				GetSprite()->SetFlipbook(FlipbooksArray[6]);
			} else if (VelX > 0 && FlipbookAtual != FlipbooksArray[7]) {
				GetSprite()->SetFlipbook(FlipbooksArray[7]);
			}
		} else {
			if (VelY < 0 && FlipbookAtual != FlipbooksArray[4]) {
				GetSprite()->SetFlipbook(FlipbooksArray[4]);
			} else if (VelY > 0 && FlipbookAtual != FlipbooksArray[5]) {
				GetSprite()->SetFlipbook(FlipbooksArray[5]);
			}
		}
	}

	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), VelY);
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), VelX);
}

TSubclassOf<class AUserProjectile> AUser::ChangeShot(int Value)
{
	return ProjectilesArray[Value];
}

