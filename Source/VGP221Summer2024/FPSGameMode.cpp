// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"
#include "Player/FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GUI/GameOverWidget.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

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

	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}

    NumberOfPlants = 0;
    NumberOfSeedCollectables = 2;
}

void AFPSGameMode::AddPlant()
{
    NumberOfPlants++;
    UE_LOG(LogTemp, Warning, TEXT("Plant added. Total Plants in level: %d"), NumberOfPlants);
}

void AFPSGameMode::RemovePlant()
{
    if (NumberOfPlants > 0)
    {
        NumberOfPlants--;
        UE_LOG(LogTemp, Warning, TEXT("Plant removed. Total Plants in level: %d"), NumberOfPlants);
        CheckGameOver();
    }
}

void AFPSGameMode::AddSeedCollectable()
{
    NumberOfSeedCollectables++;
    UE_LOG(LogTemp, Warning, TEXT("SeedCollectable added. Total SeedCollectables in level: %d"), NumberOfSeedCollectables);
}

void AFPSGameMode::RemoveSeedCollectable()
{
    if (NumberOfSeedCollectables > 0)
    {
        NumberOfSeedCollectables--;
        UE_LOG(LogTemp, Warning, TEXT("SeedCollectable removed. Total SeedCollectables in level: %d"), NumberOfSeedCollectables);

        CheckGameOverWithDelay();
    }
}

void AFPSGameMode::CheckGameOver()
{
    UE_LOG(LogTemp, Warning, TEXT("Checking for game over"));
    AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (!PlayerCharacter) return; 

    bool bHasActiveSeedProjectiles = ActiveSeedProjectiles.Num() > 0;

    if (PlayerCharacter->GetPlayerSeedCount() >= 5)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player won!"));
        GameOver(true); 
        return;
    }

    if (PlayerCharacter->GetPlayerSeedCount() <= 0 && NumberOfPlants <= 0 && NumberOfSeedCollectables <= 0 && !bHasActiveSeedProjectiles)
    {
        UE_LOG(LogTemp, Warning, TEXT("Should be game over"));
        GameOver(false);
        return;
    }

}

void AFPSGameMode::CheckGameOverWithDelay()
{
    FTimerHandle GameOverTimerHandle;

    GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, this, &AFPSGameMode::CheckGameOver, 1.0f, false);
}

void AFPSGameMode::GameOver(bool bPlayerWon)
{
    UE_LOG(LogTemp, Warning, TEXT("Game over function running"));
    // If we have a valid GameOverWidgetClass, create the widget
    if (GameOverWidgetClass)
    {
        GameOverWidgetInstance = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);

        if (GameOverWidgetInstance)
        {
            GameOverWidgetInstance->AddToViewport();

            GameOverWidgetInstance->SetIsFocusable(true);

            // Set the GameOver text depending on whether the player won or lost
            if (bPlayerWon)
            {
                GameOverWidgetInstance->SetGameOverText("You Win!");
            }
            else
            {
                GameOverWidgetInstance->SetGameOverText("Game Over, no seeds left!");
            }

            // Set input mode to UI only and show the mouse cursor
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;

                UE_LOG(LogTemp, Warning, TEXT("Is widget focusable: %s"), GameOverWidgetInstance->IsFocusable() ? TEXT("Yes") : TEXT("No"));
            }
        }
    }
}

void AFPSGameMode::RegisterSeedProjectile(ASeedProjectile* Projectile)
{
    if (Projectile)
    {
        ActiveSeedProjectiles.Add(Projectile);
    }
}

void AFPSGameMode::UnregisterSeedProjectile(ASeedProjectile* Projectile)
{
    if (Projectile)
    {
        ActiveSeedProjectiles.Remove(Projectile);
    }
}
