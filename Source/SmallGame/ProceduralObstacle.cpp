#include "ProceduralObstacle.h"

AProceduralObstacle::AProceduralObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("PCG_Mesh");
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProceduralMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ProceduralMesh->SetGenerateOverlapEvents(true);
	ProceduralMesh->SetupAttachment(GetRootComponent());
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

	ProceduralMesh->OnComponentBeginOverlap.AddDynamic(this, &AProceduralObstacle::OnOverlapBegin);
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
