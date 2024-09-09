// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/Collectable.h"
#include "Kismet/GameplayStatics.h"
#include "WaterCollectable.generated.h"


/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API AWaterCollectable : public ACollectable
{
	GENERATED_BODY()
	
public:
	AWaterCollectable();

private:
	TSubclassOf<class AFPSProjectile> WaterProjectileClass;

protected:
	virtual void BeginPlay() override;

public:
	// Override the OnCollect method
	virtual void OnCollect() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* WaterCollectableMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UMaterialInstanceDynamic* WaterCollectableMaterialInstance;

};
