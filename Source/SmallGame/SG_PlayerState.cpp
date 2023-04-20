#include "SG_PlayerState.h"
#include "PlayerBase.h"

void ASG_PlayerState::BeginPlay()
{
	Super::BeginPlay();	
	
	APlayerBase* Pawn = Cast<APlayerBase>(GetPawn());
	if(Pawn)
	{
		startPos = Pawn->GetActorLocation();
	}
}

void ASG_PlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetScore(FVector::Distance(GetPawn()->GetActorLocation(), startPos) / 250.f);
}
