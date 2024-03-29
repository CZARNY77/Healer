// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "HealerPlayer.h"
#include "Components/SphereComponent.h"
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
	UPROPERTY(EditAnywhere, Category = "Slime Settings")
	USphereComponent* MyCollisionSphere;
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	AHealerPlayer* Player;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TakeDamage(int dmg);


private:
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	float speed;
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	float SphereRadius;
	UPROPERTY(EditAnywhere, category = "Slime Settings")
	int hp;
};
