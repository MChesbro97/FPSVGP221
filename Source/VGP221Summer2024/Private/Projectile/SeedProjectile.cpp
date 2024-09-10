 // Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SeedProjectile.h"
#include "Plants/Plant.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "UObject/ConstructorHelpers.h"

ASeedProjectile::ASeedProjectile()
{
	// Override any default properties specific to SeedProjectile
	if (ProjectileMeshComponent)
	{
		// Load a seed-specific material
		static ConstructorHelpers::FObjectFinder<UMaterial> SeedMaterial(TEXT("/Game/Materials/M_Seed.M_Seed"));
		if (SeedMaterial.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SeedMaterial.Object, ProjectileMeshComponent);
			ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
			UE_LOG(LogTemp, Warning, TEXT("SeedProjectile material successfully applied!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find Seed Material!"));
		}

		// Optional: Adjust the size if needed
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.12f, 0.12f, 0.12f));
	}

	PlantClass = APlant::StaticClass();
}

void ASeedProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Call the parent OnHit method (optional depending on whether you need the parent behavior)
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	UE_LOG(LogTemp, Warning, TEXT("OnHit event called!"));

	// Check if the hit object is the ground (or any object you want to spawn the plant on)
	if (OtherActor && OtherActor->ActorHasTag("Ground"))  // Example tag check for "Ground"
	{
		if (PlantClass)  // Ensure PlantClass is valid
		{
			FVector SpawnLocation = Hit.ImpactPoint;  // Location where the plant will be spawned
			FRotator SpawnRotation = FRotator::ZeroRotator;  // You can adjust this as needed

			// Spawn the plant
			APlant* SpawnedPlant = GetWorld()->SpawnActor<APlant>(PlantClass, SpawnLocation, SpawnRotation);

			if (SpawnedPlant)
			{
				UE_LOG(LogTemp, Warning, TEXT("Plant spawned successfully at location %s"), *SpawnLocation.ToString());
			}
		}
	}

	// Destroy the SeedProjectile after it spawns the plant
	Destroy();
}

// Called when the game starts or when spawned
void ASeedProjectile::BeginPlay()
{
	Super::BeginPlay();

	// You can add any seed-specific behavior here if needed
}
