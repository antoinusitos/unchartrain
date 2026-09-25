// Fill out your copyright notice in the Description page of Project Settings.

#include "UCT_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UCT_Interactable.h"
#include "UCT_Canon.h"

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
	
	LocalController = Cast<APlayerController>(GetController());
}

// Called every frame
void AUCT_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled())
	{
		return;
	}

	CheckFrontForHint();

	CheckReloading();

	if (CurrentInteractableUsed != nullptr && CurrentInteractableUsed->ShouldReceiveMouseInput)
	{
		Server_SendMouseDeltaToInteraction(CurrentInteractableUsed.Get(), LastMouseXDelta, LastMouseYDelta);
	}
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

	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &AUCT_Player::Interaction);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AUCT_Player::Reload);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Released, this, &AUCT_Player::StopReload);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AUCT_Player::Fire);
}

void AUCT_Player::MoveForward(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (CurrentInteractableUsed != nullptr)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), Value);
}

void AUCT_Player::MoveRight(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}

	if (CurrentInteractableUsed != nullptr)
	{
		return;
	}

	AddMovementInput(GetActorRightVector(), Value);
}

void AUCT_Player::LookAround(float Value)
{
	LastMouseXDelta = Value;

	if (Value == 0.0f)
	{
		return;
	}

	if (CurrentInteractableUsed != nullptr)
	{
		return;
	}

	AddControllerYawInput(Value);
}

void AUCT_Player::LookUp(float Value)
{
	LastMouseYDelta = Value;

	if (Value == 0.0f)
	{
		return;
	}

	if (CurrentInteractableUsed != nullptr)
	{
		return;
	}

	CameraRotation = FMath::Clamp(CameraRotation + Value, -89.0f, 89.0f);

	SpringArmComponent->SetRelativeRotation(FRotator(CameraRotation, 0, 0));
}

void AUCT_Player::CheckFrontForHint()
{
	if (CurrentInteractableUsed != nullptr)
	{
		return;
	}

	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * InteractionRange;
	FHitResult Result;

	if (GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility))
	{
		if (Result.GetActor()->IsA(AUCT_Interactable::StaticClass()))
		{
			ShowHint(Cast<AUCT_Interactable>(Result.GetActor())->Hint.ToString());
		}
		else
		{
			ShowHint("");
		}
	}
	else
	{
		ShowHint("");
	}
}

void AUCT_Player::Interaction()
{
	if (CurrentInteractableUsed != nullptr)
	{
		if (CurrentInteractableUsed->ReplaceCameraWhenAttached)
		{
			LocalController->SetViewTargetWithBlend(this);
		}

		Server_DetachToInteraction(CurrentInteractableUsed.Get());

		CurrentInteractableUsed = nullptr;
		
		return;
	}

	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * InteractionRange;
	FHitResult Result;

	if (GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility))
	{
		if (Result.GetActor()->IsA(AUCT_Interactable::StaticClass()))
		{
			CurrentInteractableUsed = Cast<AUCT_Interactable>(Result.GetActor());
			ShowHint(CurrentInteractableUsed->UsingInstructions.ToString());
			if (CurrentInteractableUsed->PlayerNeedAttachTo)
			{
				Server_AttachToInteraction(CurrentInteractableUsed.Get());
			}
			if (CurrentInteractableUsed->ReplaceCameraWhenAttached)
			{
				LocalController->SetViewTargetWithBlend(CurrentInteractableUsed.Get());
			}
		}
	}
}

void AUCT_Player::Server_AttachToInteraction_Implementation(AUCT_Interactable* Interactable)
{
	if (Interactable == nullptr)
	{
		return;
	}

	if (Interactable->NumberPeopleUsing >= Interactable->NumberPlayersMax)
	{
		return;
	}

	Interactable->AttachToInteractable(this);

	if (Interactable->ReplacePlayerWhenAttached)
	{
		SetActorLocation(Interactable->GetPlayerPlacementPosition(), false, nullptr, ETeleportType::TeleportPhysics);
		GetController()->SetControlRotation(Interactable->GetPlayerPlacementRotation());
	}
}

void AUCT_Player::Server_DetachToInteraction_Implementation(AUCT_Interactable* Interactable)
{
	if (Interactable == nullptr)
	{
		return;
	}

	Interactable->DetachToInteractable(this);
}

void AUCT_Player::Reload()
{
	Reloading = true;
}

void AUCT_Player::StopReload()
{
	Reloading = false;
}

void AUCT_Player::CheckReloading()
{
	if (Reloading)
	{
		if (CurrentInteractableUsed->IsA<AUCT_Canon>())
		{
			AUCT_Canon* Canon = Cast<AUCT_Canon>(CurrentInteractableUsed);
			if (Canon->Loaded)
			{
				ShowLongInputSlider(false, 0);
			}
			else
			{
				Server_UseReloadOnInteraction(Canon);
				ShowLongInputSlider(true, Canon->CurrentReloadTime / Canon->ReloadTime);
			}
		}
		else
		{
			ShowLongInputSlider(false, 0);
		}
	}
	else
	{
		ShowLongInputSlider(false, 0);
	}
}

void AUCT_Player::Server_UseReloadOnInteraction_Implementation(AUCT_Interactable* Interactable)
{
	Interactable->UseReloadInteraction();
}


void AUCT_Player::Server_UseInteraction_Implementation(AUCT_Interactable* Interactable)
{
	Interactable->UseInteractable();
}

void AUCT_Player::Fire()
{
	if (CurrentInteractableUsed == nullptr)
	{
		return;
	}

	Server_UseInteraction(CurrentInteractableUsed.Get());
}

void AUCT_Player::Server_SendMouseDeltaToInteraction_Implementation(AUCT_Interactable* Interactable, float X, float Y)
{
	Interactable->ReceiveMouseInput(X, Y);
}