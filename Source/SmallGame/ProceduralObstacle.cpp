#include "ProceduralObstacle.h"

#include "PlayerBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AProceduralObstacle::AProceduralObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("PCG_Mesh");
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProceduralMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ProceduralMesh->SetGenerateOverlapEvents(true);
	ProceduralMesh->SetupAttachment(GetRootComponent());
	ScoreVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Score1"));
	ScoreVolume->SetupAttachment(ProceduralMesh);
	ScoreVolume->SetBoxExtent(FVector(5, 150, 250));
}

void AProceduralObstacle::BeginPlay()
{
	Super::BeginPlay();

	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> uvs;
	TArray<FVector> normals;

	float startY = -(Width / 2.f);
	float endY = FMath::RandRange(300.f, Width - 400.f);
	float startY2 = startY + endY + 300.f;
	AddQuad(vertices, triangles, uvs, normals, FVector4(startY, endY, 0, 500));
	AddQuad(vertices, triangles, uvs, normals, FVector4(startY2, Width - (startY2 - startY), 0, 500));
	AddQuad(vertices, triangles, uvs, normals, FVector4(startY, Width, 500, 100));

	ProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uvs,
	                                              TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);

	ProceduralMesh->SetMaterial(0, Material);

	ScoreVolume->SetRelativeLocation(FVector(0, startY2 - 150, 250));
	
	ProceduralMesh->OnComponentBeginOverlap.AddDynamic(this, &AProceduralObstacle::OnOverlapBegin);
	ScoreVolume->OnComponentBeginOverlap.AddDynamic(this, &AProceduralObstacle::OnOverlapScore);
}

void AProceduralObstacle::AddQuad(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs,
                                  TArray<FVector> normals, const FVector4& size)
{
	vertices.Add(FVector(0, size.X, size.Z));
	vertices.Add(FVector(0, size.X, size.Z + size.W));
	vertices.Add(FVector(0, size.X + size.Y, size.Z));
	vertices.Add(FVector(0, size.X + size.Y, size.Z + size.W));

	const int triangleIndexOffset = QuadCount * 4;
	triangles.Add(0 + triangleIndexOffset);
	triangles.Add(2 + triangleIndexOffset);
	triangles.Add(1 + triangleIndexOffset);
	triangles.Add(2 + triangleIndexOffset);
	triangles.Add(3 + triangleIndexOffset);
	triangles.Add(1 + triangleIndexOffset);

	const float uvScale = 1.f / 400.f;
	uvs.Add(FVector2D(size.X * uvScale, size.Z * uvScale));
	uvs.Add(FVector2D(size.X * uvScale, (size.Z + size.W) * uvScale));
	uvs.Add(FVector2D((size.X + size.Y) * uvScale, size.Z * uvScale));
	uvs.Add(FVector2D((size.X + size.Y) * uvScale, (size.Z + size.W) * uvScale));

	normals.Add(FVector::BackwardVector);
	normals.Add(FVector::BackwardVector);
	normals.Add(FVector::BackwardVector);
	normals.Add(FVector::BackwardVector);

	QuadCount++;
}

void AProceduralObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProceduralObstacle::OnOverlapScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APlayerBase::StaticClass())) return;

	APlayerBase* player = Cast<APlayerBase>(OtherActor);
	if (UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(player->GetController())) != ControllerID)
		return;
	player->Score();
}
