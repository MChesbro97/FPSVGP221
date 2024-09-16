// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ChickenAIController.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API AChickenAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AChickenAIController();

	// Behavior tree for the chicken
	UPROPERTY(EditAnywhere)
	UBehaviorTree* StartingBehaviorTree;


protected:
	virtual void BeginPlay() override;
};
