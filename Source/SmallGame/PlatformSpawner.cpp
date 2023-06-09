#include "PlatformSpawner.h"

#include "SmallGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ASmallGameGameModeBase* gameMode = Cast<ASmallGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if(gameMode)
		layerDistance = gameMode->TileHeight;
	
	InitFirstPlatforms();
}

void APlatformSpawner::InitFirstPlatforms()
{
	for (int i = 0; i < layerCount; i++)
		SpawnPlatform();
}

void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DistanceToNextPlatform = FVector::Dist(FVector(NextIndex * layerDistance, 0, 300), PlayerActor->GetActorLocation());
	if(DistanceToNextPlatform < SpawnDistanceThreshold)
		SpawnPlatform();
}

void APlatformSpawner::SpawnPlatform()
{
	FVector pos = FVector(NextIndex * layerDistance, 0, 200);
	GetWorld()->SpawnActor<ASpawnable>(spawnItem, GetActorForwardVector() + pos, FRotator(0, 0, 0));
	NextIndex++;
}

