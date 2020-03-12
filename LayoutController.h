// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcRamp.h"
#include "RMCPylon.h"
#include "RMCWall.h"
#include "RMCBlock.h"
#include "LayoutController.generated.h"

UCLASS()
class PAINTBALLDAVIS_API ALayoutController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALayoutController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Establish properties on the Layout Controller blueprint so that the controller knows which actors to spawn
	// when the layout is built. Everything can be found under the Spawn Objects category on the blueprint.
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Objects")
		TSubclassOf<AProcRamp> rampObject;		// The parent ramp/block object
	//	TSubclassOf<ARMCBlock> rampObject;		// The parent ramp/block object
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Objects")
		TSubclassOf<ARMCPylon> pylonObject;		// The parent pylon object
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Objects")
		TSubclassOf<ARMCWall> wallObject;		// The parent wall object

	// Below are the methods for building the various object meshes.
	// Greater details in the source code
	void BuildWalls();		// Method for building walls
	void BuildPylons();		// Method for building pylons
	void BuildRamps();		// Method for building ramps
};
