// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateEnemy.h"
#include "InfectedSlime.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGenerateEnemy::AGenerateEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenerateEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AHealerPlayer>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
}

// Called every frame
void AGenerateEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("time: %f"), time));
	if (time >= 3.f) {

		UBlueprint* BlueprintObj = Objects[0];
		if (BlueprintObj != nullptr) {
			float RandomX = FMath::RandRange(1000, 2000);
			float RandomY = FMath::RandRange(1000, 2000);
			RandomX = (int(RandomX) % 2) == 0 ? RandomX * -1 : RandomX;
			RandomY = (int(RandomY) % 2) == 0 ? RandomY * -1 : RandomY;
			FVector RandomVector(RandomX, RandomY, 0);
			FVector newLocation = Player->GetActorLocation() + RandomVector;
			GetWorld()->SpawnActor<AInfectedSlime>(BlueprintObj->GeneratedClass, newLocation, FRotator(0, 0, 0));
			time = 0.f;
		}
	}

}
