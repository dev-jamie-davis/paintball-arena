// Fill out your copyright notice in the Description page of Project Settings.

#include "RMCWall.h"


// Sets default values
ARMCWall::ARMCWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh from the runtime mesh component
	mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("GeneratedMesh"));
	// And make it the root component
	RootComponent = mesh;

	// MATERIAL AND TEXTURE

	static ConstructorHelpers::FObjectFinder <UMaterial> asset(TEXT("Material'/Game/Materials/stoneMat.stoneMat'"));
	m_dynamicMaterial = asset.Object;

}

// Called when the game starts or when spawned
void ARMCWall::BeginPlay()
{
	Super::BeginPlay();
	// Get our initial location, which we'll reference to set our new location
	// Does UE provide a more efficient way to do this?
	oldLocation = GetActorLocation();
	myRotation.ZeroRotator;
	// Apply a random rotation value between 0 and 359 (just a hair short of 360 degrees)
	myRotation.Yaw = FMath::RandRange(0, 359);
	// Randomize a starting X axis location somewhere within our arena
	myLocation.X = FMath::RandRange(-1000, 1000);
	// Randomize a starting Y axis value, too
	myLocation.Y = FMath::RandRange(-1000, 1000);
	// Align our wall in relative to the height of the floor
	myLocation.Z = oldLocation.Z + 120;
	// And establish our vector location and new rotation
	SetActorLocation(myLocation);
	SetActorRotation(myRotation);
	
}

// Called every frame
void ARMCWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARMCWall::PostActorCreated()
{
	Super::PostActorCreated();
	// Called whenever this actor is created. Will generate the actual box mesh.
	GenerateBoxMesh();
}

void ARMCWall::PostLoad()
{
	Super::PostLoad();
	// Called when we're loaded. Will also generate the actual box mesh when called.
	GenerateBoxMesh();
}

void ARMCWall::GenerateBoxMesh()
{
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FRuntimeMeshTangent> Tangents;
	TArray<FVector2D> TextureCoordinates;
	TArray<int32> Triangles;
	TArray<FColor> Colors;
	// Call the createboxmesh method, which will generate a wall with an X-length between 200 and 500 units, by 10 units wide, and 120 units tall.
	CreateBoxMesh(FVector(FMath::RandRange(200, 500), 10, 120), Vertices, Triangles, Normals, TextureCoordinates, Tangents, Colors);
	// Have the mesh create a section with the Runtime Mesh Component class
	mesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, Colors, Tangents, true);
}

void ARMCWall::CreateBoxMesh(FVector BoxRadius, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FRuntimeMeshTangent>& Tangents, TArray<FColor>& Colors)
{
	FVector BoxVerts[4];
	// Establish the box vertices. A standard box has eight corners, each represented by a vertex
	BoxVerts[0] = FVector(-BoxRadius.X - FMath::RandRange(-100, 100), BoxRadius.Y, BoxRadius.Z);
	BoxVerts[1] = FVector(BoxRadius.X - FMath::RandRange(-100, 100), BoxRadius.Y, BoxRadius.Z);
	BoxVerts[2] = FVector(BoxRadius.X - FMath::RandRange(-100, 100), -BoxRadius.Y, BoxRadius.Z);
	BoxVerts[3] = FVector(-BoxRadius.X - FMath::RandRange(-100, 100), -BoxRadius.Y, BoxRadius.Z);
	BoxVerts[4] = FVector(-BoxRadius.X - FMath::RandRange(-100, 100), BoxRadius.Y, -BoxRadius.Z);
	BoxVerts[5] = FVector(BoxRadius.X - FMath::RandRange(-100, 100), BoxRadius.Y, -BoxRadius.Z);
	BoxVerts[6] = FVector(BoxRadius.X - FMath::RandRange(-100, 100), -BoxRadius.Y, -BoxRadius.Z);
	BoxVerts[7] = FVector(-BoxRadius.X - FMath::RandRange(-100, 100), -BoxRadius.Y, -BoxRadius.Z);
	Triangles.Reset();
	const int32 NumVerts = 24; // 6 faces x 4 verts per face 
	Colors.Reset();
	Colors.AddUninitialized(NumVerts);
	for (int i = 0; i < NumVerts / 3; i++) {
		Colors[i * 3] = FColor(255, 0, 0);
		Colors[i * 3 + 1] = FColor(0, 255, 0);
		Colors[i * 3 + 2] = FColor(0, 0, 255);
	}
	// Per the basics of the Runtime Mesh Component plugin page
	// https://github.com/Koderz/RuntimeMeshComponent/wiki/Mesh-Basics
	// the meshes in the RMC components have two parts: the vertex buffer, which is a list containing
	// 1. the vertices, or position, which is an FVector 3D point (X, Y, Z) defined in the object-spage
	// 2. normals, which are used to control lighting along with 
	// 3. the tangent
	// 4. the vertex colors, which in this method are red, blue, or green determined in multiples of 3
	// 5. the texture coordinates, in FVector2D, which are used to align textures on the mesh
	// The second part is the index or triangle buffer, which links all of the vertices into
	// triangles that make up the faces.
	Vertices.Reset();
	Vertices.AddUninitialized(NumVerts);
	Normals.Reset();
	Normals.AddUninitialized(NumVerts);
	Tangents.Reset();
	Tangents.AddUninitialized(NumVerts);
	Vertices[0] = BoxVerts[0];
	Vertices[1] = BoxVerts[1];
	Vertices[2] = BoxVerts[2];
	Vertices[3] = BoxVerts[3];
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(3);
	Normals[0] = Normals[1] = Normals[2] = Normals[3] = FVector(0, 0, 1);
	Tangents[0] = Tangents[1] = Tangents[2] = Tangents[3] = FRuntimeMeshTangent(0.f, -1.f, 0.f);
	Vertices[4] = BoxVerts[4];
	Vertices[5] = BoxVerts[0];
	Vertices[6] = BoxVerts[3];
	Vertices[7] = BoxVerts[7];
	Triangles.Add(4);
	Triangles.Add(5);
	Triangles.Add(7);
	Triangles.Add(5);
	Triangles.Add(6);
	Triangles.Add(7); //bottom 
	Normals[4] = Normals[5] = Normals[6] = Normals[7] = FVector(-1, 0, 0);
	Tangents[4] = Tangents[5] = Tangents[6] = Tangents[7] = FRuntimeMeshTangent(0.f, -1.f, 0.f);
	Vertices[8] = BoxVerts[5];
	Vertices[9] = BoxVerts[1];
	Vertices[10] = BoxVerts[0];
	Vertices[11] = BoxVerts[4];
	Triangles.Add(8);
	Triangles.Add(9);
	Triangles.Add(11);
	Triangles.Add(9);
	Triangles.Add(10);
	Triangles.Add(11);
	Normals[8] = Normals[9] = Normals[10] = Normals[11] = FVector(0, 1, 0);
	Tangents[8] = Tangents[9] = Tangents[10] = Tangents[11] = FRuntimeMeshTangent(-1.f, 0.f, 0.f);
	Vertices[12] = BoxVerts[6];
	Vertices[13] = BoxVerts[2];
	Vertices[14] = BoxVerts[1];
	Vertices[15] = BoxVerts[5];
	Triangles.Add(12);
	Triangles.Add(13);
	Triangles.Add(15);
	Triangles.Add(13);
	Triangles.Add(14);
	Triangles.Add(15);
	Normals[12] = Normals[13] = Normals[14] = Normals[15] = FVector(1, 0, 0);
	Tangents[12] = Tangents[13] = Tangents[14] = Tangents[15] = FRuntimeMeshTangent(0.f, 1.f, 0.f);
	Vertices[16] = BoxVerts[7];
	Vertices[17] = BoxVerts[3];
	Vertices[18] = BoxVerts[2];
	Vertices[19] = BoxVerts[6];
	Triangles.Add(16);
	Triangles.Add(17);
	Triangles.Add(19);
	Triangles.Add(17);
	Triangles.Add(18);
	Triangles.Add(19);
	Normals[16] = Normals[17] = Normals[18] = Normals[19] = FVector(0, -1, 0);
	Tangents[16] = Tangents[17] = Tangents[18] = Tangents[19] = FRuntimeMeshTangent(1.f, 0.f, 0.f);
	Vertices[20] = BoxVerts[7];
	Vertices[21] = BoxVerts[6];
	Vertices[22] = BoxVerts[5];
	Vertices[23] = BoxVerts[4];
	Triangles.Add(20);
	Triangles.Add(21);
	Triangles.Add(23);
	Triangles.Add(21);
	Triangles.Add(22);
	Triangles.Add(23);
	Normals[20] = Normals[21] = Normals[22] = Normals[23] = FVector(0, 0, -1);
	Tangents[20] = Tangents[21] = Tangents[22] = Tangents[23] = FRuntimeMeshTangent(0.f, 1.f, 0.f); // UVs 
	UVs.Reset();
	UVs.AddUninitialized(NumVerts);
	UVs[0] = UVs[4] = UVs[8] = UVs[12] = UVs[16] = UVs[20] = FVector2D(0.f, 0.f);
	UVs[1] = UVs[5] = UVs[9] = UVs[13] = UVs[17] = UVs[21] = FVector2D(0.f, 1.f);
	UVs[2] = UVs[6] = UVs[10] = UVs[14] = UVs[18] = UVs[22] = FVector2D(1.f, 1.f);
	UVs[3] = UVs[7] = UVs[11] = UVs[15] = UVs[19] = UVs[23] = FVector2D(1.f, 0.f);
}

void ARMCWall::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Create a dynamic material instance to swap in the fog texture.  
	if (m_dynamicMaterial) {
		m_dynamicMaterialInstance = UMaterialInstanceDynamic::Create(m_dynamicMaterial, this);
		m_dynamicMaterialInstance->SetTextureParameterValue("StoneTexture", m_dynamicTexture);
	}
	// Set the dynamic material to the mesh.  
	if (m_dynamicMaterialInstance) mesh->SetMaterial(0, m_dynamicMaterialInstance);
}