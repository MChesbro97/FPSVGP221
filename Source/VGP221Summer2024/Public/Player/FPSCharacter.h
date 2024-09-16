// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile/FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "FPSCharacter.generated.h"

UCLASS()
class VGP221SUMMER2024_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	//TSubclassOf<class AFPSProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> DefaultProjectileClass;
	TSubclassOf<class AFPSProjectile> WaterProjectileClass;
	TSubclassOf<class AFPSProjectile> SeedProjectileClass;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRightNotTheSameAsInput(float value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void SetProjectileClass(TSubclassOf<class AFPSProjectile> NewProjectileClass);

	UFUNCTION()
	void SetWaterProjectile();

	UFUNCTION()
	void SetSeedProjectile();

	UFUNCTION()
	void SetDefaultProjectile();

	float Health = 100;
	const float MaxHealth = 100;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int Seeds;

	void IncreaseSeeds(int amount);
	void DecreaseSeeds(int amount);
	int GetPlayerSeedCount() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int Water; 

	void IncreaseWater(int Amount);
	void DecreaseWater(int Amount);
	int GetPlayerWaterCount() const;
};

