#include "GroundBlock.h"
#include "Probability.h"
#include "SmallGameGameModeBase.h"

AGroundBlock::AGroundBlock()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGroundBlock::BeginPlay()
{
	Super::BeginPlay();
	
	ASmallGameGameModeBase* gameMode = Cast<ASmallGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if(gameMode)
		Size = FVector(gameMode->TileHeight / 100, gameMode->TileWidth / 100, 1);
	BlockInit();
}

void AGroundBlock::BlockInit()
{
	UWorld* world = GetWorld();
	AActor* ground = world->SpawnActor<AActor>(GroundCube, GetActorLocation(), FRotator(0, 0, 0));
	ground->SetActorScale3D(Size);

	for (int i = 1; i <= ObstaclePerBlock; i++)
	{
		float x = (i / static_cast<float>(ObstaclePerBlock)) * Size.X * 100;
		x = (GetActorLocation().X - Size.X * 100 / 2) + x;
		FVector location = FVector(x, GetActorLocation().Y, GetActorLocation().Z);
		TSubclassOf<ASpawnable> spawnItem = UProbability::GetWeightedRandomElement(Obstacles, Probabilities);
		ASpawnable* spawnable = world->SpawnActor<ASpawnable>(spawnItem, location, FRotator(0, 0, 0));
		spawnable->SetWidth(Size.Y);
	}
}

// Called every frame
void AGroundBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

