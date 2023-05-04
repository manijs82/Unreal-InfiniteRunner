#include "Spawnable.h"
#include "PlayerBase.h"
#include "SmallGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASpawnable::ASpawnable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnable::BeginPlay()
{
	Super::BeginPlay();
	
	ASmallGameGameModeBase* gameMode = Cast<ASmallGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if(gameMode)
	{
		DestroyDistanceThreshold = gameMode->DestroyDistanceThreshold;
		Width = gameMode->TileWidth;
	}
}

void ASpawnable::SetID(int ID)
{
	ControllerID = ID;
	
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), ControllerID);
	Cast<APlayerBase>(PlayerActor)->OnScore.AddDynamic(this, &ASpawnable::DestroyWithChance);
}

void ASpawnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceSpawn += DeltaTime;
	
	DistanceFromPlayer = GetDistanceFromPlayer();
	DestroyIfFar();
}

float ASpawnable::GetDistanceFromPlayer()
{
	if(!PlayerActor)
		PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), ControllerID);
	return PlayerActor->GetActorLocation().X - GetActorLocation().X;
}

void ASpawnable::DestroyIfFar()
{
	if(DistanceFromPlayer >= DestroyDistanceThreshold)
		Destroy();
}

void ASpawnable::DestroyWithChance()
{
	if(FMath::RandRange(0.f, 1.f) < 0.25f && TimeSinceSpawn < 10.f)
	{
		Destroy();
	}
}

void ASpawnable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APlayerBase::StaticClass())) return;

	APlayerBase* player = Cast<APlayerBase>(OtherActor);
	player->Hit();
}

