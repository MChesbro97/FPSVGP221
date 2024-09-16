// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTT_EatSeed.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_EatSeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the AI controller
	AChickenAIController* AIOwner = Cast<AChickenAIController>(OwnerComp.GetAIOwner());
	if (!AIOwner) return EBTNodeResult::Failed;

	// Get the target seed from the blackboard
	ASeedCollectable* Seed = Cast<ASeedCollectable>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Seed")));
	if (!Seed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Seed Target is null"));
		return EBTNodeResult::Failed;
	}

	// "Eat" the seed by destroying the seed actor
	Seed->Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Seed has been eaten"));

	// After eating the seed, clear the Seed Target in the blackboard
	OwnerComp.GetBlackboardComponent()->ClearValue(FName("Seed"));

	return EBTNodeResult::Succeeded;
}

