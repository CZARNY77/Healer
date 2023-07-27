// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Blueprint.h"
#include "GameFramework/Pawn.h"
#include "HealerPlayer.generated.h"

UCLASS()
class HEALER_API AHealerPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHealerPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* MainRoot;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* PlayerFlipbook;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* MyCollisionCapsule;

	UFUNCTION()
	void DetectionSlime(float dt);
	UFUNCTION()
	void heal(FHitResult Slime);
	UFUNCTION()
	UBlueprint* LoadCuredSlime();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TakeDamage(int dmg);


private:

	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, category = "Healer Settings")
	float speed;
	UPROPERTY(EditAnywhere, category = "Healer Settings")
	int hp;

	bool bIsEnlargingSphere;
	float Radius;
};
