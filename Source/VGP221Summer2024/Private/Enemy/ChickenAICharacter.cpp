// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChickenAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AChickenAICharacter::AChickenAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ChickenMesh = GetMesh();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChickenMeshAsset(TEXT("/Game/Meshes/Chicken.Chicken"));
	if (ChickenMeshAsset.Succeeded())
	{

		ChickenMesh->SetSkeletalMesh(ChickenMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> ChickenMaterialAsset(TEXT("/Game/Meshes/Main.Main"));
	if (ChickenMaterialAsset.Succeeded())
	{
		ChickenMesh->SetMaterial(0, ChickenMaterialAsset.Object);
	}

	//ChickenMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); 
	//ChickenMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void AChickenAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChickenAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


