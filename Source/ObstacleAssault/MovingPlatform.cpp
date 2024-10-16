#include "MovingPlatform.h"

/* Sets default values */
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

/* Called when the game starts or when spawned */
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

/* Called every frame */
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

/* To move the platform */
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Send platform back if gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	// Move platform forwards
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

/* To rotate the platform */
void AMovingPlatform::RotatePlatform(float DeltaTime) 
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

/* Check if the platform should return or not */
bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

/* Return the current distance moved */
float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
