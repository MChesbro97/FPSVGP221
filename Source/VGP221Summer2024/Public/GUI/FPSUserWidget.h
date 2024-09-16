// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GUI/ButtonWidget.h"
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SeedsText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* WaterBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaterText;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UButtonWidget> ButtonWidgetPrefab;

	UFUNCTION()
	void SetHealthBar(float percentage);

	UFUNCTION()
	void IncreaseSeedsText(int amount);
	UFUNCTION()
	void DecreaseSeedsText(int amount);
	UFUNCTION()
	void IncreaseWaterText(int amount);
	UFUNCTION()
	void DecreaseWaterText(int amount);

private:
	int UISeeds = 0;

	int UIWater = 0;
};
