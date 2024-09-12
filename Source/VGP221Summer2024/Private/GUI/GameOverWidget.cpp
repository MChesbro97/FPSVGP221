// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	SetGameOverText("Game Over, no seeds left!");
	SetButtonText("Play Again", "Quit To Main Menu");

	// Bind button click events
	if (PlayAgainButton)
	{
		PlayAgainButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnPlayAgainClicked);
	}

	if (QuitToMainMenuButton)
	{
		QuitToMainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnQuitToMainMenuClicked);
	}

}

void UGameOverWidget::SetGameOverText(FString NewGameOverText)
{
	if (GameOverText)
	{
		GameOverText->SetText(FText::FromString(NewGameOverText));
	}
}

void UGameOverWidget::SetButtonText(FString NewPlayAgainButtonText, FString NewQuitToMainMenuButtonText)
{
	if (PlayAgainButtonText)
	{
		PlayAgainButtonText->SetText(FText::FromString(NewPlayAgainButtonText));
	}

	if (QuitToMainMenuButtonText)
	{
		QuitToMainMenuButtonText->SetText(FText::FromString(NewQuitToMainMenuButtonText));
	}
}

void UGameOverWidget::OnPlayAgainClicked()
{
	// Restart the current level
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void UGameOverWidget::OnQuitToMainMenuClicked()
{
	// Open the Main Menu level
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}