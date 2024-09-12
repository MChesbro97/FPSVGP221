// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/SeedCollectable.h"
#include "Player/FPSCharacter.h"
#include "VGP221Summer2024/FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Projectile/FPSProjectile.h"
#include "Projectile/SeedProjectile.h"

ASeedCollectable::ASeedCollectable()
{
	// Set up the mesh for the seed collectable
	SeedCollectableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seed_ANIMATION_Seed"));
	SeedCollectableMeshComponent->SetupAttachment(CollisionComponent);

	// Load the static mesh for the seed collectable (make sure the path is correct)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Meshes/Seed_ANIMATION_Seed.Seed_ANIMATION_Seed"));
	if (MeshAsset.Succeeded())
	{
		SeedCollectableMeshComponent->SetStaticMesh(MeshAsset.Object);
		SeedCollectableMeshComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	// Optionally, load any specific materials or set up additional components if needed
}
void ASeedCollectable::BeginPlay()
{
	Super::BeginPlay();

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->AddSeedCollectable(); 
	}
}

void ASeedCollectable::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("SeedCollectable OnCollect Called"));

	// Get the player reference
	AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Player)
	{
		// Set the player's projectile class to the SeedProjectile
		Player->SetProjectileClass(ASeedProjectile::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Projectile changed to SeedProjectile!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find the player or projectile class is null."));
	}

	if (Player)
	{
		Player->IncreaseSeeds(1);  // Increase the seed count by 1 and update UI
		UE_LOG(LogTemp, Log, TEXT("Collected a seed!"));
	}

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->RemoveSeedCollectable();
	}

	// Destroy the collectable after collection
	Destroy();
}
