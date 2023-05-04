#include "MovingPlatform.h"

#include "PlayerBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	DamageVolume->SetCollisionProfileName(TEXT("Pawn"));
	FVector size = FVector(1.5f, 1.5f, 1.5f);
	DamageVolume->SetRelativeScale3D(size);
	RootComponent = DamageVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DamageVolume);
	ScoreVolume1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Score1"));
	ScoreVolume1->SetupAttachment(DamageVolume);
	ScoreVolume2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Score2"));
	ScoreVolume2->SetupAttachment(DamageVolume);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (bSetRandomDistance)
		SetRandomDistance();
	if (bSetRandomYOffset)
		SetRandomYOffset();
	if (bSetRandomSpeed)
		SetRandomSpeed();
	if (bSetRandomAxis)
		SetRandomAxis();

	StartPos = GetActorLocation();

	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnOverlapBegin);
	ScoreVolume1->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnOverlapScore);
	ScoreVolume2->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnOverlapScore);
}

void AMovingPlatform::SetRandomDistance()
{
	Distance = FMath::RandRange(0.f, Width / 2.f);
}

void AMovingPlatform::SetRandomYOffset()
{
	float maxOffset = Width / 2.f - Distance;
	float yOffset = GetActorLocation().Y + FMath::RandRange(-maxOffset, maxOffset);

	SetActorLocation(FVector(GetActorLocation().X, yOffset, GetActorLocation().Z));
}

void AMovingPlatform::OnOverlapScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APlayerBase::StaticClass())) return;

	APlayerBase* player = Cast<APlayerBase>(OtherActor);
	if (UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(player->GetController())) != ControllerID)
		return;
	player->Score();
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
