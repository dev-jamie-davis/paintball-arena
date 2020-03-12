// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "RuntimeMeshComponent.h"
#include "RMCPylon.generated.h"

UCLASS()
class PAINTBALLDAVIS_API ARMCPylon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMCPylon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	// Define all of our mesh-related methods and members
public:
	virtual void GenerateBoxMesh(); // Called from the actor creation and loading methods, which then sends the call for the box mesh creation
									// Our actual mesh creation method
	virtual void CreateBoxMesh(FVector BoxRadius, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FRuntimeMeshTangent>& Tangents, TArray<FColor>& Colors);

public:
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;

	// We need some vector and rotator holders to keep track of our initial spawning points, as well as where we want them to go at the beginning of play
	FVector myLocation;
	FVector oldLocation;
	FRotator myRotation;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere)
		URuntimeMeshComponent* mesh; // Placeholder for the mesh object

	UPROPERTY() UTexture2D * m_dynamicTexture;
	UPROPERTY() UMaterialInterface * m_dynamicMaterial;
	UPROPERTY() UMaterialInstanceDynamic * m_dynamicMaterialInstance;
	
};
