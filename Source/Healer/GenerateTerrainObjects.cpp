// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateTerrainObjects.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
AGenerateTerrainObjects::AGenerateTerrainObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenerateTerrainObjects::BeginPlay()
{
	Super::BeginPlay();
	for (UPaperSprite* Object : Objects)
	{
		float x = FMath::RandRange(-1000.0f, 1000.0f);
		float y = FMath::RandRange(-1000.0f, 1000.0f);
		FVector SpawnLocation = FVector(x, y, 0.5f); // Lokalizacja, w której chcesz utworzyæ aktora
		FRotator SpawnRotation = FRotator(0.f, 0.f, 90.f); // Rotacja aktora (domyœlnie 0)

		// Utwórz aktora na podstawie sprite'a
		AActor* NewActor = GetWorld()->SpawnActor<AActor>();
		if (NewActor)
		{
			// Dodaj komponent PaperSpriteComponent do aktora
			UPaperSpriteComponent* SpriteComponent = NewObject<UPaperSpriteComponent>(NewActor, TEXT("PaperSpriteComponent"));
			SpriteComponent->SetSprite(Object);
			SpriteComponent->SetRelativeRotation(SpawnRotation);
			SpriteComponent->SetRelativeLocation(SpawnLocation);
			NewActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			NewActor->AddInstanceComponent(SpriteComponent);
			SpriteComponent->RegisterComponent();
		}
	}
}

// Called every frame
void AGenerateTerrainObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}