#pragma once

#include "CoreMinimal.h"
#include "Spawnable.h"
#include "ProceduralMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ProceduralObstacle.generated.h"

UCLASS()
class SMALLGAME_API AProceduralObstacle : public ASpawnable
{
	GENERATED_BODY()

public:
	AProceduralObstacle();

	UPROPERTY(EditAnywhere)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProceduralMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ScoreVolume;

private:
	int QuadCount;

protected:
	virtual void BeginPlay() override;

	void AddQuad(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs, TArray<FVector> normals, const FVector4& size);

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
