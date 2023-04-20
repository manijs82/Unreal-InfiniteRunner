#include "CameraController.h"

ACameraController::ACameraController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = PlayerCamera;
}

void ACameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Target) return;

	FVector location = FVector(Target->GetActorLocation().X, 0, Target->GetActorLocation().Z);
	SetActorLocation(location + LocationOffset);
	SetActorRotation(FRotator(RotationOffset.X, RotationOffset.Y, RotationOffset.Z));
}

void ACameraController::SetTarget(APawn* pawn)
{
	Target = pawn;
}

