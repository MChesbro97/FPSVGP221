// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChickenAIController.h"

AChickenAIController::AChickenAIController()
{
	PrimaryActorTick.bCanEverTick = true; 
}

void AChickenAIController::BeginPlay()
{
	Super::BeginPlay();

    Super::BeginPlay();

    // Ensure behavior tree is correctly assigned
    if (StartingBehaviorTree)
    {
        RunBehaviorTree(StartingBehaviorTree);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not assigned in ChickenAIController"));
    }

    RunBehaviorTree(StartingBehaviorTree);

}
