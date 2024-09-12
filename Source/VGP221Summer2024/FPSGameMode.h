// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/StructuredLog.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	void GameOver();

	void AddPlant();
	void RemovePlant();
	void AddSeedCollectable();
	void RemoveSeedCollectable();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UGameOverWidget> GameOverWidgetClass;

	UPROPERTY()
	class UGameOverWidget* GameOverWidgetInstance;

	// Track the number of plants and seed collectables
	int NumberOfPlants;
	int NumberOfSeedCollectables;

	// Check for game over conditions
	void CheckGameOver();
};
