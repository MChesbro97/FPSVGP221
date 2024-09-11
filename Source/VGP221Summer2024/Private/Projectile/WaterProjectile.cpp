// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/WaterProjectile.h"
#include "UObject/ConstructorHelpers.h"
#include "Plants/Plant.h"

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

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &AWaterProjectile::OnHit);
	}
}

// Called when the game starts or when spawned
void AWaterProjectile::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("WaterProjectile spawned, Material: %s"),
		*ProjectileMeshComponent->GetMaterial(0)->GetName());
}


void AWaterProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the hit object is a plant
	if (OtherActor && OtherActor->IsA(APlant::StaticClass()))
	{
		// Cast to APlant
		APlant* HitPlant = Cast<APlant>(OtherActor);
		if (HitPlant)
		{
			// Call the plant's watering function
			HitPlant->OnWatered(HitComponent, this, OtherComp, 0, false, Hit);
			UE_LOG(LogTemp, Warning, TEXT("WaterProjectile hit plant and called OnWatered"));

			// Destroy the water projectile after hitting the plant
			Destroy();
		}
	}
}