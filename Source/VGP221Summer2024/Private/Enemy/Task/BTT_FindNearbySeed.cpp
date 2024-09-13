// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task/BTT_FindNearbySeed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTT_FindNearbySeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AChickenAIController* AIOwner = Cast<AChickenAIController>(OwnerComp.GetAIOwner());
	if (!AIOwner) return EBTNodeResult::Failed;

	FVector ChickenLocation = AIOwner->GetPawn()->GetActorLocation();

	TArray<AActor*> FoundSeeds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASeedCollectable::StaticClass(), FoundSeeds);

	if (FoundSeeds.Num() == 0) return EBTNodeResult::Failed;

	ASeedCollectable* ClosestSeed = nullptr;
	float MinDistance = SearchRadius;

	for (AActor* SeedActor : FoundSeeds)
	{
		ASeedCollectable* Seed = Cast<ASeedCollectable>(SeedActor);
		if (Seed)
		{
			float Distance = FVector::Dist(ChickenLocation, Seed->GetActorLocation());

			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestSeed = Seed;
			}
		}
	}

	if (ClosestSeed)
	{
		FVector SeedLocation = ClosestSeed->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Seed"), ClosestSeed);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
