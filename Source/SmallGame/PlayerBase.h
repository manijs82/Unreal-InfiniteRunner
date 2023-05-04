// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingQuery.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "PlayerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDieEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreEvent);

UCLASS()
class SMALLGAME_API APlayerBase : public APawn
{
	GENERATED_BODY()

public:
	APlayerBase();

	UPROPERTY(BlueprintAssignable, Category="Health")
	FDieEvent OnDie;
	UPROPERTY(BlueprintAssignable, Category="Health")
	FHitEvent OnHit;
	UPROPERTY(BlueprintAssignable, Category="Health")
	FScoreEvent OnScore;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
	int HitPoints;
	UPROPERTY(BlueprintReadOnly)
	int Health;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float HorizontalSpeed = 7;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardSpeed = 3;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

protected:
	virtual void BeginPlay() override;

	FVector StartLocation;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Hit();
	void Score();
	void Die();
	void MoveHorizontally(const FInputActionInstance& Instance);
	UPROPERTY()
	bool IsDead;
};
