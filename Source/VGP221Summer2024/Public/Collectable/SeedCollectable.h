// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/Collectable.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "SeedCollectable.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API ASeedCollectable : public ACollectable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASeedCollectable();

private:
	TSubclassOf<class AFPSProjectile> SeedProjectileClass;

protected:
	virtual void BeginPlay() override;

public:
	// Override the OnCollect method
	virtual void OnCollect() override;

	virtual void Destroyed() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* SeedCollectableMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UMaterialInstanceDynamic* SeedCollectableMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Seeds = 1;
};
