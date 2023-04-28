// Copyright Epic Games, Inc. All Rights Reserved.


#include "SmallGameGameModeBase.h"

#include "PlayerBase.h"
#include "SG_PlayerState.h"
#include "TwoPlayerMover.h"
#include "Kismet/GameplayStatics.h"

void ASmallGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AddPlayerToWorld(1, Player1, Player1SpawnPos);
	AddPlayerToWorld(2, Player2, Player2SpawnPos);
}

void ASmallGameGameModeBase::AddPlayerToWorld(int index, TSubclassOf<APlayerBase> playerClass, FVector location)
{
	FString error;
	ULocalPlayer* localPlayer = GetWorld()->GetGameInstance()->CreateLocalPlayer(index, error, true);
	APlayerController* NewPlayerController = localPlayer->GetPlayerController(GetWorld());

	if (NewPlayerController)
	{
		APawn* CreatedPlayer = NewPlayerController->GetPawn();

		if(CreatedPlayer)
		{
			CreatedPlayer->Destroy();
			NewPlayerController->UnPossess();
		}
		
		APlayerBase* PlayerTwoInWorld = GetWorld()->SpawnActor<APlayerBase>(playerClass, location, FRotator::ZeroRotator);
		if (PlayerTwoInWorld)
		{
			NewPlayerController->Possess(PlayerTwoInWorld);
		}

		APawn* p1 = UGameplayStatics::GetPlayerPawn(GetWorld(), index);
		if(p1)
		{
			p1->SetActorLocation(location);
		 	ASG_PlayerState* state = Cast<ASG_PlayerState>(p1->GetPlayerState());
			state->StartPosition = location;
		}
	}	
}
