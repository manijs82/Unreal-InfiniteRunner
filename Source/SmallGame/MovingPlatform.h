// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawnable.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UENUM(BlueprintType)
enum class AxisMode : uint8
{
	AxisX UMETA(DisplayName="X"),
	AxisY UMETA(DisplayName="Y"),
	AxisZ UMETA(DisplayName="Z"),
};

UCLASS()
class SMALLGAME_API AMovingPlatform : public ASpawnable
{
	GENERATED_BODY()
	FVector StartPos;

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	UShapeComponent* DamageVolume;
	UPROPERTY(EditAnywhere)
	UShapeComponent* ScoreVolume1;
	UPROPERTY(EditAnywhere)
	UShapeComponent* ScoreVolume2;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	bool bSetRandomYOffset = false;
	UPROPERTY(EditAnywhere)
	bool bSetRandomDistance = false;
	UPROPERTY(EditAnywhere)
	bool bSetRandomSpeed = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bSetRandomSpeed", EditConditionHides))
	float MaxSpeed = 1;
	UPROPERTY(EditAnywhere)
	bool bSetRandomAxis = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bSetRandomDistance"))
	float Distance = 600;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bSetRandomSpeed"))
	float Speed = 1;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bSetRandomAxis"))
	AxisMode AxisMode;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	FVector GetNextPosition();

	void SetRandomAxis();
	void SetRandomSpeed();
	void SetRandomDistance();
	void SetRandomYOffset();

	UFUNCTION()
	void OnOverlapScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
