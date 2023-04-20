// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingQuery.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "PlayerBase.generated.h"

UCLASS()
class SMALLGAME_API APlayerBase : public APawn
{
	GENERATED_BODY()

public:
	APlayerBase();

	UPROPERTY(EditAnywhere, Category = "Health")
	int HitPoints;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float HorizontalSpeed = 7;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardSpeed = 3;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

protected:
	virtual void BeginPlay() override;

	int Health;
	FVector StartLocation;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Hit();

	void MoveHorizontally(const FInputActionInstance& Instance);
};
