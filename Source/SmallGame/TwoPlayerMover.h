#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingQuery.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "PlayerBase.h"
#include "TwoPlayerMover.generated.h"

UCLASS()
class SMALLGAME_API ATwoPlayerMover : public APawn
{
	GENERATED_BODY()

public:
	ATwoPlayerMover();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction2;

	UPROPERTY()
	APlayerBase* Player1;
	UPROPERTY()
	APlayerBase* Player2;
	UPROPERTY()
	float ForwardSpeed = 5;

protected:
	virtual void BeginPlay() override;

	void MovePlayerOne(const FInputActionInstance& Instance);
	void MovePlayerTwo(const FInputActionInstance& Instance);
	bool AreBothDead() const;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
