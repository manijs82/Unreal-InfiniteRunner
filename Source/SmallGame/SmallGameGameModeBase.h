// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmallGameGameModeBase.generated.h"

class APlayerBase;
/**
 * 
 */
UCLASS()
class SMALLGAME_API ASmallGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Game Params")
	int TileWidth;
	UPROPERTY(EditAnywhere, Category = "Game Params")
	int TileHeight;
	UPROPERTY(EditAnywhere, Category = "Game Params")
	float DestroyDistanceThreshold;

	UPROPERTY(EditAnywhere, Category = "Players")
	TSubclassOf<APlayerBase> Player1;
	UPROPERTY(EditAnywhere, Category = "Players")
	TSubclassOf<APlayerBase> Player2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Players")
	FVector Player1SpawnPos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Players")
	FVector Player2SpawnPos;
	
};
