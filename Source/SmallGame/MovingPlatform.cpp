#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Collider->SetCollisionProfileName(TEXT("Pawn"));
	FVector size = FVector(1.5f, 1.5f, 1.5f);
	Collider->SetRelativeScale3D(size);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if(bSetRandomDistance)
		SetRandomDistance();
	if(bSetRandomYOffset)
		SetRandomYOffset();
	if(bSetRandomSpeed)
		SetRandomSpeed();
	if(bSetRandomAxis)
		SetRandomAxis();

	StartPos = GetActorLocation();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnOverlapBegin);
}

void AMovingPlatform::SetRandomDistance()
{
	Distance = FMath::RandRange(0.f, Width / 2.f);
}

void AMovingPlatform::SetRandomYOffset()
{
	float maxOffset = Width / 2.f - Distance;
	float yOffset = FMath::RandRange(-maxOffset, maxOffset);
	
	SetActorLocation(FVector(GetActorLocation().X, yOffset, GetActorLocation().Z));
}

void AMovingPlatform::SetRandomAxis()
{
	AxisMode = static_cast<enum AxisMode>(FMath::RandRange(0, 2));
}

void AMovingPlatform::SetRandomSpeed()
{
	Speed = FMath::RandRange(0.f, MaxSpeed);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetNextPosition());
}

FVector AMovingPlatform::GetNextPosition()
{
	FVector nextPos = StartPos;
	const float interpolator = FMath::Cos(UGameplayStatics::GetTimeSeconds(GetWorld()) * Speed);
	switch (AxisMode)
	{
	case AxisMode::AxisX:
		nextPos.X += interpolator * Distance;
		break;
	case AxisMode::AxisY:
		nextPos.Y += interpolator * Distance;
		break;
	case AxisMode::AxisZ:
		nextPos.Z += interpolator * Distance;
		break;
	default: ;
	}

	return nextPos;
}


