// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/WaterProjectile.h"
#include "UObject/ConstructorHelpers.h"

AWaterProjectile::AWaterProjectile()
{
	if (ProjectileMeshComponent)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> WaterMaterial(TEXT("/Game/Materials/M_Water.M_Water"));
		if (WaterMaterial.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(WaterMaterial.Object, ProjectileMeshComponent);
			if (ProjectileMaterialInstance)
			{
				ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
			}
		}

		// Optional: Adjust the size if needed
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.12f, 0.12f, 0.12f));
	}
}

// Called when the game starts or when spawned
void AWaterProjectile::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("WaterProjectile spawned, Material: %s"),
		*ProjectileMeshComponent->GetMaterial(0)->GetName());
}