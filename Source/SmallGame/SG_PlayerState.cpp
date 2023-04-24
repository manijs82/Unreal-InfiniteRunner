#include "SG_PlayerState.h"
#include "PlayerBase.h"
#include "RunnerSave.h"
#include "Kismet/GameplayStatics.h"

void ASG_PlayerState::BeginPlay()
{
	Super::BeginPlay();	

	LoadPlayerState();
	APlayerBase* pawn = Cast<APlayerBase>(GetPawn());
	if(pawn)
	{
		startPos = pawn->GetActorLocation();
		pawn->OnDie.AddDynamic(this, &ASG_PlayerState::SavePlayerState);
	}
}

void ASG_PlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetScore(FVector::Distance(GetPawn()->GetActorLocation(), startPos) / 250.f);
}

void ASG_PlayerState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SavePlayerState();
}

void ASG_PlayerState::SavePlayerState()
{
	URunnerSave* runnerSave = Cast<URunnerSave>(UGameplayStatics::CreateSaveGameObject(URunnerSave::StaticClass()));
	runnerSave->HighScore = GetScore();

	UGameplayStatics::SaveGameToSlot(runnerSave, TEXT("Save0"), 0);
}

void ASG_PlayerState::LoadPlayerState()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("Save0"), 0))
	{
		URunnerSave* runnerSave = Cast<URunnerSave>(UGameplayStatics::LoadGameFromSlot(TEXT("Save0"), 0));
		HighScore = runnerSave->HighScore;
	}
}
