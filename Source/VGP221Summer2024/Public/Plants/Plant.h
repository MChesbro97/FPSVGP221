// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Plant.generated.h"

UCLASS()
class VGP221SUMMER2024_API APlant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// Plant's mesh component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlantMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* PlantCollider;

	UFUNCTION()
	void OnWatered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void CheckGrowth();
	void DieAndDropSeeds();
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool bHasBeenWatered;

	float TimeToGrowOrDie;
	float GrowthCount;
	float MaxGrowthCount;

	FTimerHandle GrowthTimerHandle;

	FVector GrowthScale;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASeedCollectable> SeedCollectableClass;

};
