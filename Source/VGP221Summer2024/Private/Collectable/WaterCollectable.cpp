// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/WaterCollectable.h"
#include "Player/FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Projectile/FPSProjectile.h"
#include "Projectile/WaterProjectile.h"


AWaterCollectable::AWaterCollectable()
{
		WaterCollectableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Diamond3D"));
		WaterCollectableMeshComponent->SetupAttachment(CollisionComponent);
		// Load the static mesh for the water collectable (make sure the path is correct)
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Meshes/Diamond3D.Diamond3D"));
		if (MeshAsset.Succeeded())
		{
			WaterCollectableMeshComponent->SetStaticMesh(MeshAsset.Object);

			WaterCollectableMeshComponent->SetRelativeScale3D(FVector(100.0f, 100.0f, 100.0f));
		}

}

void AWaterCollectable::BeginPlay()
{
	Super::BeginPlay();
}
void AWaterCollectable::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("WaterCollectable OnCollect Called"));

	AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Player)
	{
		// Directly set the projectile class to the native C++ WaterProjectile class
		Player->SetProjectileClass(AWaterProjectile::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Projectile changed to WaterProjectile!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find the player or projectile class is null."));
	}

	Destroy();
}

