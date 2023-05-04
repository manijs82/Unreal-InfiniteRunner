#pragma once

#include "CoreMinimal.h"
#include "Spawnable.h"
#include "GameFramework/Actor.h"
#include "GroundBlock.generated.h"

class AMovingPlatform;

UCLASS()
class SMALLGAME_API AGroundBlock : public ASpawnable
{
	GENERATED_BODY()

public:
	AGroundBlock();

	UPROPERTY(EditAnywhere)
	int ObstaclePerBlock = 3;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> GroundCube;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASpawnable>> Obstacles;
	UPROPERTY(EditAnywhere)
	TArray<float> Probabilities;
	FVector Size;

protected:
	virtual void BeginPlay() override;
	void BlockInit();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetID(int ID) override;
};
