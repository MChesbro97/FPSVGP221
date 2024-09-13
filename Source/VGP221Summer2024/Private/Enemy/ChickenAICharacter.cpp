// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChickenAICharacter.h"

// Sets default values
AChickenAICharacter::AChickenAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChickenAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChickenAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


