// Copyright Epic Games, Inc. All Rights Reserved.


#include "SmallGameGameModeBase.h"

#include "PlayerBase.h"
#include "SG_PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ASmallGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* NewPlayerController = Cast<APlayerController>(
		UGameplayStatics::CreatePlayer(GetWorld(), 1));

	if (NewPlayerController != nullptr)
	{
		APawn* CreatedPlayer = NewPlayerController->GetPawn();

		if(CreatedPlayer)
		{
			// DESTROY NEW PLAYER ONE and any new classes you aren't going to use
			CreatedPlayer->Destroy();
			NewPlayerController->UnPossess();

			// UnPossess the newly created APlayerController

			// Spawn player two
			APlayerBase* PlayerTwoInWorld = GetWorld()->SpawnActor<APlayerBase>(Player2, Player2SpawnPos, FRotator::ZeroRotator);

			if (PlayerTwoInWorld != nullptr)
			{
				// Have player two possess APlayerController at index 1
				NewPlayerController->Possess(PlayerTwoInWorld);
			}
		}
	}
}
