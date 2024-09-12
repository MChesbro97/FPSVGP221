// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    UPROPERTY(meta = (BindWidget))
        class UTextBlock* TitleText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayButtonText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* QuitButtonText;

    UPROPERTY(meta = (BindWidget))
        class UButton* PlayButton;

    UPROPERTY(meta = (BindWidget))
        UButton* QuitButton;

    void SetTitleText(FString NewTitle);
    void SetButtonText(FString NewPlayButtonText, FString NewQuitButtonText);

private:
    UFUNCTION()
        void OnPlayClicked();

    UFUNCTION()
        void OnQuitClicked();
	
};
