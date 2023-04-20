
#pragma once

#include "CoreMinimal.h"
#include "Spawnable.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class SMALLGAME_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpawnable> spawnItem;
	UPROPERTY(EditAnywhere)
	int layerCount = 3;
	UPROPERTY(EditAnywhere)
	int SpawnDistanceThreshold = 1000;
	int layerDistance = 300;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* PlayerActor;
	float DistanceToNextPlatform;
	int NextIndex;

public:	
	virtual void Tick(float DeltaTime) override;
	void InitFirstPlatforms();
	void SpawnPlatform();

};
