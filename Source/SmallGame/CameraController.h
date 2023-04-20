#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "CameraController.generated.h"

UCLASS()
class SMALLGAME_API ACameraController : public AActor
{
	GENERATED_BODY()

public:
	ACameraController();

	UPROPERTY(EditAnywhere)
	FVector LocationOffset;
	UPROPERTY(EditAnywhere)
	FVector RotationOffset;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

private:
	UPROPERTY()
	APawn* Target;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(APawn* pawn);
};
