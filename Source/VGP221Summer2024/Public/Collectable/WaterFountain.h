// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WaterFountain.generated.h"

class AWaterCollectable;

UCLASS()
class VGP221SUMMER2024_API AWaterFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnWaterCollectable();

	UFUNCTION()
	void OnCollectableCollected(AActor* CollectableActor);

	UPROPERTY(VisibleAnywhere, Category = "Fountain")
	UStaticMeshComponent* FountainMesh;

	UPROPERTY(VisibleAnywhere, Category = "Fountain")
	UBoxComponent* FountainCollision;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TSubclassOf<AWaterCollectable> WaterCollectableClass;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	int32 WaterCollectablesToSpawn = 1; 

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	float SpawnDelay = 5.0f;

	bool bIsCollectablePresent;
};
