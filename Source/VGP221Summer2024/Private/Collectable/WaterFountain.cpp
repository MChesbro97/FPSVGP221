// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/WaterFountain.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Collectable/WaterCollectable.h" 

// Sets default values
AWaterFountain::AWaterFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FountainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FountainMesh"));
	RootComponent = FountainMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FountainMeshAsset(TEXT("/Game/Meshes/Fountain.Fountain"));
	if (FountainMeshAsset.Succeeded())
	{
		FountainMesh->SetStaticMesh(FountainMeshAsset.Object);
		FountainMesh->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> WaterMaterial(TEXT("/Game/Materials/M_Water.M_Water"));
	if (WaterMaterial.Succeeded())
	{
		FountainMesh->SetMaterial(0, WaterMaterial.Object);
	}

	//FountainCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FountainCollision"));
	//FountainCollision->InitBoxExtent(FVector(6.0f, 6.0f, 6.0f));
	//FountainCollision->SetRelativeLocation(FVector(0, 0, 5));
	//FountainCollision->SetupAttachment(FountainMesh);
	//FountainCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	bIsCollectablePresent = false;

	WaterCollectableClass = AWaterCollectable::StaticClass();
}


// Called when the game starts or when spawned
void AWaterFountain::BeginPlay()
{
	Super::BeginPlay();
	SpawnWaterCollectable();
}

// Called every frame
void AWaterFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterFountain::SpawnWaterCollectable()
{
	if (WaterCollectableClass && !bIsCollectablePresent)
	{
		// Determine spawn location and rotation (in front of the fountain)
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150.0f;  // Spawn in front of the fountain
		FRotator SpawnRotation = FRotator::ZeroRotator;

		// Spawn the water collectable
		AWaterCollectable* Collectable = GetWorld()->SpawnActor<AWaterCollectable>(WaterCollectableClass, SpawnLocation, SpawnRotation);

		if (Collectable)
		{
			// Bind to the collectable's OnCollect event
			Collectable->OnDestroyed.AddDynamic(this, &AWaterFountain::OnCollectableCollected);

			// Mark that a collectable is present
			bIsCollectablePresent = true;

			UE_LOG(LogTemp, Warning, TEXT("Water collectable spawned at location: %s"), *SpawnLocation.ToString());
		}
	}
}

void AWaterFountain::OnCollectableCollected(AActor* CollectableActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Water collectable collected"));

	// Mark that there is no collectable present
	bIsCollectablePresent = false;

	// Start a timer to spawn a new collectable after a delay
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaterFountain::SpawnWaterCollectable, SpawnDelay, false);
}



