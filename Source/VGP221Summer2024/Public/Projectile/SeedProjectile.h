// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/FPSProjectile.h"
#include "SeedProjectile.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API ASeedProjectile : public AFPSProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASeedProjectile();

protected:
	// Override BeginPlay to initialize any seed-specific behavior
	virtual void BeginPlay() override;
};
