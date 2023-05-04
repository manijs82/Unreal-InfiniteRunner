#include "PlayerBase.h"

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PlayerMesh;
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	Health = HitPoints;
	StartLocation = GetActorLocation();
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += ForwardSpeed;
	SetActorLocation(NewLocation);
	if(!IsDead)
	{
		ForwardSpeed += 0.05f * DeltaTime;
		ForwardSpeed = FMath::Clamp(ForwardSpeed, 0, 12);
	}
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerBase::Hit()
{
	Health--;
	OnHit.Broadcast();
	if(Health <= 0)
	{
		Die();	
	}
}

void APlayerBase::Score()
{
	if(!IsDead)
		OnScore.Broadcast();
}

void APlayerBase::Die()
{
	if(IsDead) return;
	IsDead = true;
	HorizontalSpeed = 0;
	ForwardSpeed = 0;
	OnDie.Broadcast();
}

void APlayerBase::MoveHorizontally(const FInputActionInstance& Instance)
{
	float horizontal = Instance.GetValue().Get<float>();
	FVector NewLocation = GetActorLocation();
	NewLocation.Y += horizontal * HorizontalSpeed;
	SetActorLocation(NewLocation);
}
