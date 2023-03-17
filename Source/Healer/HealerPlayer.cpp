// Fill out your copyright notice in the Description page of Project Settings.


#include "HealerPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AHealerPlayer::AHealerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	MainRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Main Root"));
	PlayerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Player Flipbook"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Camera"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	PlayerFlipbook->SetupAttachment(MainRoot);

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(MainRoot);

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AHealerPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerController != nullptr) {
		PlayerController->bShowMouseCursor = true;
		PlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;
	}
}

// Called every frame
void AHealerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	bool bHitSuccessful = PlayerController != nullptr ? PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit) : false;

	if (bHitSuccessful) {
		FVector2D CurrentLocation2D(Hit.Location.X, Hit.Location.Y);
		FVector2D ActorLocation2D(GetActorLocation().X, GetActorLocation().Y);
		FVector2D Direction = (CurrentLocation2D - ActorLocation2D).GetSafeNormal();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("X: %f"), Direction.X));
		if (Direction.X > 0) PlayerFlipbook->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		else PlayerFlipbook->SetRelativeRotation(FRotator(0.f, 180.f, -90.f));
		SetActorLocation(FVector(ActorLocation2D + Direction * speed * DeltaTime, GetActorLocation().Z));
	}



}

// Called to bind functionality to input
void AHealerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

