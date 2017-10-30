// Fill out your copyright notice in the Description page of Project Settings.

#include "User.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

AUser::AUser()
{
	//Altera o tamanho e rotaçao do personagem em relação ao cenário.
	RootComponent->SetRelativeScale3D(FVector(0.15f, 0.5f, 0.15f));
	RootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	//Altera as dimensões do capsule component.
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(100.0f);

	//Inicializa e configura o Camera Boom.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->SetupAttachment(RootComponent);

	//Inicializa e configura a Camera.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 512.0f;
	Camera->SetupAttachment(CameraBoom);

	//Inicializa o sprite (UPaperFlipbook) do personagem.
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleSprite(TEXT("PaperFlipbook'/Game/Sprites/Sorcerer.Sorcerer'"));
	if (IdleSprite.Succeeded()) { Idle = IdleSprite.Object; }
	GetSprite()->SetFlipbook(Idle);

	//Adiciona "controle" do usuário ao personagem.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Altera a velocidade maxima do personagem.
	GetCharacterMovement()->MaxWalkSpeed = 250;

}

void AUser::BeginPlay()
{
	Super::BeginPlay();
}

void AUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUser::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Inputs de movimentação do personagem.
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AUser::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &AUser::MoveUpDown);

	//Inputs que definem ações chamando métodos.

}

void AUser::MoveLeftRight(float Value)
{
	//Movimenta personagem para esquerda/direita.
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AUser::MoveUpDown(float Value)
{
	//Movimenta personagem para cima/baixo.
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
}


