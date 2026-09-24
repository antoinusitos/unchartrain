// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AUCT_Player::AUCT_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AUCT_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUCT_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUCT_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUCT_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUCT_Player::MoveRight);
	PlayerInputComponent->BindAxis("LookAround", this, &AUCT_Player::LookAround);
	PlayerInputComponent->BindAxis("LookUp", this, &AUCT_Player::LookUp);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);
}

void AUCT_Player::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AUCT_Player::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AUCT_Player::LookAround(float Value)
{
	AddControllerYawInput(Value);
}

void AUCT_Player::LookUp(float Value)
{
	CameraRotation = FMath::Clamp(CameraRotation + Value, -89.0f, 89.0f);

	SpringArmComponent->SetRelativeRotation(FRotator(CameraRotation, 0, 0));
}