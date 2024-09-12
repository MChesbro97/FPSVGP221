// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameOverText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayAgainButtonText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitToMainMenuButtonText;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayAgainButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitToMainMenuButton;

	void SetGameOverText(FString NewGameOverText);
	void SetButtonText(FString NewPlayAgainButtonText, FString NewQuitToMainMenuButtonText);

private:
	UFUNCTION()
	void OnPlayAgainClicked();

	UFUNCTION()
	void OnQuitToMainMenuClicked();



	
};
