// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/Plant.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the mesh component and set it as the root component
	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Oats"));
	RootComponent = PlantMesh;

	// Optionally load a default mesh or material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlantMeshAsset(TEXT("/Game/Meshes/Oats.Oats"));
	if (PlantMeshAsset.Succeeded())
	{
		PlantMesh->SetStaticMesh(PlantMeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}


