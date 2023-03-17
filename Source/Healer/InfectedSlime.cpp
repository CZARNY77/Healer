// Fill out your copyright notice in the Description page of Project Settings.


#include "InfectedSlime.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInfectedSlime::AInfectedSlime()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Infected Slime"));

}

// Called when the game starts or when spawned
void AInfectedSlime::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AHealerPlayer>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
}

// Called every frame
void AInfectedSlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player != nullptr) {
		FVector2D CurrentLocation2D(Player->GetActorLocation().X, Player->GetActorLocation().Y);
		FVector2D ActorLocation2D(GetActorLocation().X, GetActorLocation().Y);
		FVector2D Direction = (CurrentLocation2D - ActorLocation2D).GetSafeNormal();
		if (Direction.X > 0) PaperFlipbook->SetRelativeRotation(FRotator(0.f, 180.f, -90.f));
		else PaperFlipbook->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		SetActorLocation(FVector(ActorLocation2D + Direction * speed * DeltaTime, GetActorLocation().Z));
	}
}

// Called to bind functionality to input
void AInfectedSlime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

