// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Set default text for the title and buttons
	SetTitleText("FPS (Farming Projectile Shooter)");
	SetButtonText("Play", "Quit");

	// Bind functionality to the buttons
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::SetTitleText(FString NewTitle)
{
	if (TitleText)
	{
		TitleText->SetText(FText::FromString(NewTitle));
	}
}

void UMainMenuWidget::SetButtonText(FString NewPlayButtonText, FString NewQuitButtonText)
{
	if (PlayButtonText)
	{
		PlayButtonText->SetText(FText::FromString(NewPlayButtonText));
	}

	if (QuitButtonText)
	{
		QuitButtonText->SetText(FText::FromString(NewQuitButtonText));
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	FString LevelName = "FPSMap";
	FName GameModeName = "FPSGameMode";
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), true, FString::Printf(TEXT("GameMode=%s"), *GameModeName.ToString()));


}


void UMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

