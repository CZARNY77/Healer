// Fill out your copyright notice in the Description page of Project Settings.


#include "CuredSlime.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACuredSlime::ACuredSlime()
{
	PrimaryActorTick.bCanEverTick = true;
	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Cured Slime"));

	SphereRadius = 10.0f;
	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Slime Sphere Collider"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(PaperFlipbook);
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACuredSlime::OnOverlapBegin);

	bIsEnlargingSphere = true;
	Radius = 1.f;
}

// Called when the game starts or when spawned
void ACuredSlime::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACuredSlime::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor == TargetSlime) && (OtherActor != this) && (OtherComp != nullptr)) {
		TargetSlime->TakeDamage(1);
		Destroy();
	}
}

void ACuredSlime::TargetDetection(float dt)
{
	float MaxRadius = 500.f;
	int EnlargingSpeed = 400;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * Radius;

	TArray<FHitResult> OutHits;
	bool bOverlap = GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(Radius));

	if (bOverlap)
	{
		for (auto& Hit : OutHits)
		{
			if (Hit.GetActor()->ActorHasTag("Slime"))
			{
				TargetSlime = Cast<AInfectedSlime>(Hit.GetActor());
				bIsEnlargingSphere = false;
				break;
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
		bIsEnlargingSphere = true;
	}
}

// Called every frame
void ACuredSlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetSlime != nullptr) {
		FVector2D CurrentLocation2D(TargetSlime->GetActorLocation().X, TargetSlime->GetActorLocation().Y);
		FVector2D ActorLocation2D(GetActorLocation().X, GetActorLocation().Y);
		FVector2D Direction = (CurrentLocation2D - ActorLocation2D).GetSafeNormal();
		if (Direction.X > 0) PaperFlipbook->SetRelativeRotation(FRotator(0.f, 180.f, -90.f));
		else PaperFlipbook->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		SetActorLocation(FVector(ActorLocation2D + Direction * speed * DeltaTime, GetActorLocation().Z));
	}
	if (bIsEnlargingSphere)	TargetDetection(DeltaTime);
}

// Called to bind functionality to input
void ACuredSlime::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

