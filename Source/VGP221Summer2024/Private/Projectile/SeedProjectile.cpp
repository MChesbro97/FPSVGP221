// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SeedProjectile.h"
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
}

// Called when the game starts or when spawned
void ASeedProjectile::BeginPlay()
{
	Super::BeginPlay();

	// You can add any seed-specific behavior here if needed
}
