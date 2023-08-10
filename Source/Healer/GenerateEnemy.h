// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealerPlayer.h"
#include "GameFramework/Actor.h"
#include "GenerateEnemy.generated.h"

UCLASS()
class HEALER_API AGenerateEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AHealerPlayer* Player;
	float time;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TArray<class UBlueprint*> Objects;
};
