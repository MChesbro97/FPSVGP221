// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/Plant.h"
#include "Collectable/SeedCollectable.h"
#include "VGP221Summer2024/FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Projectile/WaterProjectile.h"


// Sets default values
APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = false;

	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Oats"));
	RootComponent = PlantMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlantMeshAsset(TEXT("/Game/Meshes/Oats.Oats"));
	if (PlantMeshAsset.Succeeded())
	{
		PlantMesh->SetStaticMesh(PlantMeshAsset.Object);
		PlantMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	PlantCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PlantCollider"));
	PlantCollider->SetBoxExtent(FVector(25, 300, 100), false);
	PlantCollider->SetRelativeLocation(FVector(0, 0, 100));
	PlantCollider->SetupAttachment(PlantMesh);

	bHasBeenWatered = false;

	TimeToGrowOrDie = 5.0f;

	GrowthScale = FVector(1.0f, 1.0f, 1.5f);
	GrowthCount = 0;
	MaxGrowthCount = 3;

	SeedCollectableClass = ASeedCollectable::StaticClass();
}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(GrowthTimerHandle, this, &APlant::CheckGrowth, TimeToGrowOrDie, false);

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->AddPlant();  // Call AddPlant when the plant is spawned
	}

}

void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlant::OnWatered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AWaterProjectile::StaticClass()))
	{
		// Set the plant as watered
		bHasBeenWatered = true;

		// Log or debug to confirm
		UE_LOG(LogTemp, Warning, TEXT("Plant has been watered!"));
	}
}

void APlant::CheckGrowth()
{
	if (bHasBeenWatered)
	{
		// If the plant has grown less than 3 times, it grows
		if (GrowthCount < MaxGrowthCount)
		{
			// Plant grows (doubles in size)
			FVector NewScale = GetActorScale3D() * GrowthScale;
			SetActorScale3D(NewScale);

			// Increment growth count
			GrowthCount++;
			UE_LOG(LogTemp, Warning, TEXT("Plant has grown %d times!"), GrowthCount);
		}
		else
		{
			// Plant dies and drops SeedCollectables
			DieAndDropSeeds();
			return;
		}

		// Reset watered status and start checking again
		bHasBeenWatered = false;

		// Reset the timer to check for growth again
		GetWorldTimerManager().SetTimer(GrowthTimerHandle, this, &APlant::CheckGrowth, TimeToGrowOrDie, false);
	}
	else
	{
		AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
		if (GameMode)
		{
			GameMode->RemovePlant();  // Call RemovePlant when the plant is destroyed
		}
		// If not watered, the plant dies
		Destroy();
	}
}


void APlant::DieAndDropSeeds()
{
	// Log death before destruction
	UE_LOG(LogTemp, Warning, TEXT("Plant has died!"));

	// Randomly drop between 1 and 5 seeds
	int32 SeedCount = FMath::RandRange(1, 5);

	// Get the plant's base location
	FVector PlantLocation = GetActorLocation();
	FVector PlantFootLocation = PlantLocation; // Initialize with the current plant location

	// Adjust Y coordinate to simulate seeds dropping at the base of the plant
	// You can tweak this value based on your plant's mesh height
	PlantFootLocation.Z += 50;

	// Loop to spawn seeds at the plant's base
	for (int32 i = 0; i < SeedCount; i++)
	{
		// Add slight randomness to seed spawn location for variety
		FVector SeedSpawnLocation = PlantFootLocation + FVector(0, FMath::RandRange(-150.0f, 150.0f), 0);

		// Spawn each seed collectable at the base of the plant's location
		if (SeedCollectableClass)
		{
			FRotator SpawnRotation = FRotator::ZeroRotator;  // Default rotation for seeds

			// Spawn the seed collectable
			ASeedCollectable* SpawnedSeed = GetWorld()->SpawnActor<ASeedCollectable>(SeedCollectableClass, SeedSpawnLocation, SpawnRotation);

			if (SpawnedSeed)
			{
				UE_LOG(LogTemp, Warning, TEXT("Seed collectable spawned at %s!"), *SeedSpawnLocation.ToString());
			}
		}
	}
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->RemovePlant();  // Call RemovePlant when the plant is destroyed
	}

	// Finally, destroy the plant
	Destroy();
}


