
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawnable.generated.h"

UCLASS()
class SMALLGAME_API ASpawnable : public AActor
{
	GENERATED_BODY()

public:
	ASpawnable();

protected:
	virtual void BeginPlay() override;

	virtual float GetDistanceFromPlayer();
	virtual void DestroyIfFar();

	UPROPERTY()
	AActor* PlayerActor;
	float DistanceFromPlayer;
	float Width;
	float DestroyDistanceThreshold;

public:
	virtual void Tick(float DeltaTime) override;

	void SetWidth(float width) { Width = width * 100; }
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
