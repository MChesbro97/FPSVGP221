// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/FPSProjectile.h"
#include "WaterProjectile.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API AWaterProjectile : public AFPSProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWaterProjectile();

protected:
	// Override BeginPlay to change water-specific properties
	virtual void BeginPlay() override;
};
