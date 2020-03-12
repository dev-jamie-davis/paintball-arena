// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"


// Sets default values
AMyActor::AMyActor()
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::PostActorCreated()
{
	Super::PostActorCreated();
	CreateSquare();
}

void AMyActor::PostLoad()
{
	Super::PostLoad();
	CreateSquare();
}

void AMyActor::CreateSquare()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FLinearColor> Colors;
	
	Vertices.Add(FVector(0.f, 0.f, 0.f));
	Vertices.Add(FVector(0.f, 100.f, 0.f));
	Vertices.Add(FVector(0.f, 0.f, 100.f));
	Vertices.Add(FVector(0.f, 100.f, 100.f));
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(3);
	Triangles.Add(2);
	Triangles.Add(1);

	for (int32 i = 0; i < Vertices.Num(); i++) {
		Normals.Add(FVector(0.f, 0.f, 1.f));
			Colors.Add(FLinearColor::Red);
	}
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents; 


	// For fun and experimentation, I tried to see if I could build a simple pyramid here. 
	// My vertices are good, but it became obvious very quickly that assembling the triangles
	// in the proper order (I had some weeeeird geometry in the first couple runs) will take a lot of practice, never mind also
	// adding the normals, tangents, and UVs.

	/* Vertices.Add(FVector(0.f, 0.f, 0.f));
	Vertices.Add(FVector(50.f, 0.f, 0.f));
	Vertices.Add(FVector(25.f, 50.f, 0.f));
	Vertices.Add(FVector(25.f, 25.f, 50.f));
	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(1);

	Triangles.Add(3);
	Triangles.Add(2);
	Triangles.Add(0);

	Triangles.Add(3);
	Triangles.Add(1);
	Triangles.Add(2);

	Triangles.Add(3);
	Triangles.Add(0);
	Triangles.Add(1);


	for (int32 i = 0; i < Vertices.Num(); i++) {
		Normals.Add(FVector(0.f, 0.f, 1.f));
		Colors.Add(FLinearColor::Red);
	}
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents; */

	mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, Colors, Tangents, true);
}