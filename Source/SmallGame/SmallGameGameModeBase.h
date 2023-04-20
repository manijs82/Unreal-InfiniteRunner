// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmallGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SMALLGAME_API ASmallGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int TileWidth;
	UPROPERTY(EditAnywhere)
	int TileHeight;
	UPROPERTY(EditAnywhere)
	float DestroyDistanceThreshold;
};
