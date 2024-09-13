// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ChickenAIController.h"
#include "BTT_GetRandomLocationChicken.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UBTT_GetRandomLocationChicken : public UBTTaskNode
{
	GENERATED_BODY()

public:
	FVector RandomLocation;
	UNavigationSystemV1* NavArea;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
