#include "SG_PlayerState.h"
#include "RunnerSave.h"
#include "Kismet/GameplayStatics.h"

void ASG_PlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ASG_PlayerState::InitState(APlayerBase* pawn)
{
	LoadPlayerState();
	if (pawn)
	{
		pawn->OnDie.AddDynamic(this, &ASG_PlayerState::SavePlayerState);
		pawn->OnHit.AddDynamic(this, &ASG_PlayerState::DecreaseScore);
	}
}

void ASG_PlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPawn())
		SetScore(FVector::Distance(GetPawn()->GetActorLocation(), StartPosition) / 1000.f + ScoreOffset);
}

void ASG_PlayerState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SavePlayerState();
}

void ASG_PlayerState::SavePlayerState()
{
	if (GetScore() < HighScore) return;
	URunnerSave* runnerSave = Cast<URunnerSave>(UGameplayStatics::CreateSaveGameObject(URunnerSave::StaticClass()));
	runnerSave->HighScore = FMath::FloorToInt(GetScore());

	UGameplayStatics::SaveGameToSlot(
		runnerSave, FString::FromInt(UGameplayStatics::GetPlayerControllerID(GetPlayerController())), 0);
}

void ASG_PlayerState::LoadPlayerState()
{
	if (UGameplayStatics::DoesSaveGameExist(
		FString::FromInt(UGameplayStatics::GetPlayerControllerID(GetPlayerController())), 0))
	{
		URunnerSave* runnerSave = Cast<URunnerSave>
		(UGameplayStatics::LoadGameFromSlot(
			FString::FromInt(UGameplayStatics::GetPlayerControllerID(GetPlayerController())), 0));
		HighScore = runnerSave->HighScore;
	}
}

void ASG_PlayerState::DecreaseScore()
{
	ScoreOffset--;
}
