#include "Spawnable.h"
#include "PlayerBase.h"
#include "SmallGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASpawnable::ASpawnable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnable::BeginPlay()
{
	Super::BeginPlay();
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	ASmallGameGameModeBase* gameMode = Cast<ASmallGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if(gameMode)
	{
		DestroyDistanceThreshold = gameMode->DestroyDistanceThreshold;
		Width = gameMode->TileWidth;
	}
}

void ASpawnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DistanceFromPlayer = GetDistanceFromPlayer();
	DestroyIfFar();
}

float ASpawnable::GetDistanceFromPlayer()
{
	return PlayerActor->GetActorLocation().X - GetActorLocation().X;
}

void ASpawnable::DestroyIfFar()
{
	if(DistanceFromPlayer >= DestroyDistanceThreshold)
		Destroy();
}

void ASpawnable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp,
										 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APlayerBase::StaticClass())) return;

	APlayerBase* player = Cast<APlayerBase>(OtherActor);
	player->Hit();
}

