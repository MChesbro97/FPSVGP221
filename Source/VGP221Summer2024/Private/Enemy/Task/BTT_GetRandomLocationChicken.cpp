// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTT_GetRandomLocationChicken.h"

EBTNodeResult::Type UBTT_GetRandomLocationChicken::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 1. Get random point of nav mesh
	// 2. Set the random patrol location to the new nav mesh value
	// 3. Return succeed or failed if we were able to get nav mesh value
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (NavArea)
	{
		AChickenAIController* AIOwner = Cast<AChickenAIController>(OwnerComp.GetAIOwner());
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), AIOwner->GetPawn()->GetActorLocation(), RandomLocation, 2000.0f);
	}
	else {
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Random Patrol Location"), RandomLocation);

	return EBTNodeResult::Succeeded;
}