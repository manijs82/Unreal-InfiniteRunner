#include "TwoPlayerMover.h"

#include "Kismet/GameplayStatics.h"

ATwoPlayerMover::ATwoPlayerMover()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATwoPlayerMover::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(-1500, 0, 300));
}

void ATwoPlayerMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += ForwardSpeed;
	if(!AreBothDead())
	{
		SetActorLocation(NewLocation);
		ForwardSpeed += 0.05f * DeltaTime;
	}
}

void ATwoPlayerMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* PC = Cast<APlayerController>(GetController());
	check(Input && PC);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATwoPlayerMover::MovePlayerOne);
	Input->BindAction(MoveAction2, ETriggerEvent::Triggered, this, &ATwoPlayerMover::MovePlayerTwo);
	
	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	check(LocalPlayer);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputContext, 0);
	}
}

void ATwoPlayerMover::MovePlayerOne(const FInputActionInstance& Instance)
{
	if(!Player1)
	{
		Player1 = Cast<APlayerBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
		return;
	}
	Player1->MoveHorizontally(Instance);
}

void ATwoPlayerMover::MovePlayerTwo(const FInputActionInstance& Instance)
{
	if(!Player2)
	{
		Player2 = Cast<APlayerBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 2));
		return;
	}
	Player2->MoveHorizontally(Instance);
}

bool ATwoPlayerMover::AreBothDead() const
{
	if(!Player1) return false;
	if(!Player2) return false;
	if(Player1->IsDead && Player2->IsDead) return true;
	return false;
}

