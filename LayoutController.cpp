// Fill out your copyright notice in the Description page of Project Settings.

#include "LayoutController.h"


// Sets default values
ALayoutController::ALayoutController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALayoutController::BeginPlay()
{
	Super::BeginPlay();


	// At the beginning of play, we call each building method to produce the various RMC and procedural mesh structures.
	BuildRamps();	// Procedural mesh blocks that can be jumped on.

	BuildWalls();	// Long, high walls via the runtime mesh component

	BuildPylons();	// Free-standing pylons
	
}

// Called every frame
void ALayoutController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Begin code for building methods: walls, pylons, and blocks (ramps)
// We're only really concerned with spawning the objects here. The BeginPlay method in each
// class will handle the dimensions, rotation, and randomized placement of the pieces.
/* ---------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------*/
void ALayoutController::BuildWalls()
{
	for (int i = 0; i < 8; i++)
	{
		// Begin by spawning eight wall objects [RMCWall]
	    
		// Zero out the rotation, and set the height to the default project's floor height. 
		// The class code will sort out the rest.
		FRotator startRot;
		startRot.ZeroRotator;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;
		// Spawn an actor based on the blueprint setting for the runtime mesh component-based wall.
		ARMCWall* newWallObject = GetWorld()->SpawnActor<ARMCWall>(wallObject, FVector(0, 0, 170), startRot, spawnParams);
	}
}

void ALayoutController::BuildPylons()
{
	for (int i = 0; i < 10; i++)
	{
		// Next, spawn ten pylons [RMCPylon]

		// Zero out the rotation, and set the height to the default project's floor height. 
		// The class code will sort out the rest.
		FRotator startRot;
		startRot.ZeroRotator;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;
		// Spawn an actor based on the blueprint setting for the runtime mesh component-based pylon.
		ARMCPylon* newWallObject = GetWorld()->SpawnActor<ARMCPylon>(pylonObject, FVector(0, 0, 170), startRot, spawnParams);
	}
}

void ALayoutController::BuildRamps()
{
	for (int i = 0; i < 5; i++)
	{
		// Finally, spawn five blocks [ProcRamp]

		// Zero out the rotation, and set the height to the default project's floor height. 
		// The class code will sort out the rest.
		FRotator startRot;
		startRot.ZeroRotator;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;
		// Spawn an actor based on the blueprint setting for the procedural mesh component-based block.
		AProcRamp* newWallObject = GetWorld()->SpawnActor<AProcRamp>(rampObject, FVector(0, 0, 170), startRot, spawnParams);
		//ARMCBlock* newWallObject = GetWorld()->SpawnActor<ARMCBlock>(rampObject, FVector(0, 0, 170), startRot, spawnParams);
	}
/* ---------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------*/
}