
#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "GameFramework/Actor.h"
#include "Spawnable.generated.h"

UCLASS()
class SMALLGAME_API ASpawnable : public AActor
{
	GENERATED_BODY()

public:
	ASpawnable();

	UPROPERTY()
	int ControllerID = 0;

protected:
	virtual void BeginPlay() override;

	virtual float GetDistanceFromPlayer();
	virtual void DestroyIfFar();
	UFUNCTION()
	void DestroyWithChance();

	UPROPERTY()
	AActor* PlayerActor;
	float DistanceFromPlayer;
	float Width;
	float DestroyDistanceThreshold;
	float TimeSinceSpawn;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetID(int ID);
	void SetWidth(float width) { Width = width * 100; }
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
