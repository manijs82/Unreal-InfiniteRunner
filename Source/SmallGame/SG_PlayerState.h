// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "GameFramework/PlayerState.h"
#include "SG_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SMALLGAME_API ASG_PlayerState : public APlayerState
{
	GENERATED_BODY()

	
public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	void InitState(APlayerBase* pawn);
	

	UPROPERTY(BlueprintReadOnly)
	float HighScore;
	UPROPERTY(BlueprintReadOnly)
	FVector StartPosition;

protected:
	UFUNCTION()
	void SavePlayerState();
	UFUNCTION()
	void LoadPlayerState();
	UFUNCTION()
	void DecreaseScore();
	UFUNCTION()
	void IncreaseScore();

	int ScoreOffset;
};
