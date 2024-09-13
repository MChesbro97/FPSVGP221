// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Collectable/SeedCollectable.h"
#include "Enemy/ChickenAIController.h"
#include "BTT_EatSeed.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UBTT_EatSeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
