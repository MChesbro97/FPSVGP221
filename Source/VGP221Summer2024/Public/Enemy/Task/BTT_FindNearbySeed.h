// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Collectable/SeedCollectable.h"
#include "Enemy/ChickenAIController.h"
#include "BTT_FindNearbySeed.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UBTT_FindNearbySeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// Radius within which the chicken will search for seeds
	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchRadius = 1000.0f;

	// Function to execute the task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
