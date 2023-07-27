// Fill out your copyright notice in the Description page of Project Settings.


#include "HealerPlayer.h"
#include "DrawDebugHelpers.h"
#include "CuredSlime.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


AHealerPlayer::AHealerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	hp = 5;

	MainRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Main Root"));
	PlayerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Player Flipbook"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Camera"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyCollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Capsule Collider"));

	PlayerFlipbook->SetupAttachment(MainRoot);

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(MainRoot);

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MyCollisionCapsule->SetCollisionProfileName("Trigger");
	MyCollisionCapsule->SetupAttachment(MainRoot);
	//MyCollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHealerPlayer::OnOverlapBegin);

	bIsEnlargingSphere = true;
	Radius = 1.f;
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
	if(bIsEnlargingSphere)	DetectionSlime(DeltaTime);
}

// Called to bind functionality to input
void AHealerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHealerPlayer::TakeDamage(int dmg)
{
	hp -= dmg;
}

void AHealerPlayer::DetectionSlime(float dt)
{
	//mo¿e trochê optymalizacyjnie z³e
	float MaxRadius = 500.f;
	int EnlargingSpeed = 400;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * Radius;

	TArray<FHitResult> OutHits;
	bool bOverlap = GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(Radius));

	//DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 50, FColor::Purple, true);

	if (bOverlap)
	{
		for (auto&Hit : OutHits)
		{
			if (Hit.GetActor()->ActorHasTag("Slime")) // Sprawdzenie czy obiekt ma tag "Slime"
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Closest Slime found at distance: %f"), Hit.GetActor().Distance));

				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUObject(this, &AHealerPlayer::heal, Hit);
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
				bIsEnlargingSphere = false;
				break; // Przerwanie dzia³ania pêtli po znalezieniu pierwszego obiektu z tagiem "Slime"
			}
		}
	}

	// Powiêkszanie sfery
	if (bIsEnlargingSphere && Radius < MaxRadius)
	{
		Radius += EnlargingSpeed * dt;
	}
	else
	{
		Radius = 1.f;
	}
}

void AHealerPlayer::heal(FHitResult slime)
{

	FVector SlimeLocation = slime.GetActor()->GetActorLocation();
	UBlueprint* BlueprintObj = LoadCuredSlime();
	slime.GetActor()->Destroy();
	if (BlueprintObj != nullptr) {
		GetWorld()->SpawnActor<ACuredSlime>(BlueprintObj->GeneratedClass, SlimeLocation, FRotator(0,0,0));
	}
	//GetWorld()->SpawnActor<ABP_CuredSlime>(SlimeLocation, SlimeRotator);
	bIsEnlargingSphere = true;
}

UBlueprint* AHealerPlayer::LoadCuredSlime()
{
	FString BlueprintPath = TEXT("/Game/BP_Content/BP_CuredSlime.BP_CuredSlime");
	UBlueprint* BlueprintObj = LoadObject<UBlueprint>(nullptr, *BlueprintPath);

	if (!BlueprintObj) {
		UE_LOG(LogTemp, Error, TEXT("Nie uda³o siê wczytaæ blueprinta z '%s'"), *BlueprintPath);
		return nullptr;
	}

	if (!BlueprintObj->GeneratedClass->IsChildOf(ACuredSlime::StaticClass())) {
		UE_LOG(LogTemp, Error, TEXT("Blueprint '%s' nie jest zespo³kowany do klasy ACuredSlime"), *BlueprintPath);
		return nullptr;
	}

	return BlueprintObj;
}



