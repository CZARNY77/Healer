// Fill out your copyright notice in the Description page of Project Settings.


#include "HealerPlayer.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AHealerPlayer::AHealerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Player Sprite"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Camera"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(PlayerSprite);

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AHealerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHealerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

