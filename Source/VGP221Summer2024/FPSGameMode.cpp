// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GUI/GameOverWidget.h"
#include "Blueprint/UserWidget.h"

void AFPSGameMode::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Hello World, this is FPSGameMode!"));

    // Debugging in the console
    UE_LOG(LogTemp, Warning, TEXT("Hello World, this is FPSGameMode!"));

	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Switch the input mode to Game Only, so the player can interact with the game world
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;  // Hide the cursor while playing
	}

    NumberOfPlants = 0;
    NumberOfSeedCollectables = 2;
}

void AFPSGameMode::AddPlant()
{
    NumberOfPlants++;
}

void AFPSGameMode::RemovePlant()
{
    if (NumberOfPlants > 0)
    {
        NumberOfPlants--;
        CheckGameOver();
    }
}

void AFPSGameMode::AddSeedCollectable()
{
    NumberOfSeedCollectables++;
}

void AFPSGameMode::RemoveSeedCollectable()
{
    if (NumberOfSeedCollectables > 0)
    {
        NumberOfSeedCollectables--;
        CheckGameOver();
    }
}

void AFPSGameMode::CheckGameOver()
{
    if (NumberOfPlants <= 0 && NumberOfSeedCollectables <= 0)
    {
        GameOver();
    }
}

void AFPSGameMode::GameOver()
{
    // If we have a valid GameOverWidgetClass, create the widget
    if (GameOverWidgetClass)
    {
        GameOverWidgetInstance = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);

        if (GameOverWidgetInstance)
        {
            GameOverWidgetInstance->AddToViewport();

            // Set input mode to UI only and show the mouse cursor
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;
            }
        }
    }
}
