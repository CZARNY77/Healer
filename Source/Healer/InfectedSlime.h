// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "HealerPlayer.h"
#include "GameFramework/Pawn.h"
#include "InfectedSlime.generated.h"

UCLASS()
class HEALER_API AInfectedSlime : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInfectedSlime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* PaperFlipbook;
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	AHealerPlayer* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	float speed;
};
