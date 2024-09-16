// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0f);
	IncreaseSeedsText(0);
	//IncreaseWaterText(0);
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::IncreaseSeedsText(int amount)
{
	if (!SeedsText) return;

	UISeeds += amount;
	SeedsText->SetText(FText::FromString("Seeds: " + FString::FromInt(UISeeds)));
}

void UFPSUserWidget::DecreaseSeedsText(int amount)
{
	if (!SeedsText) return;

	UISeeds = FMath::Max(0, UISeeds - amount);
	SeedsText->SetText(FText::FromString("Seeds: " + FString::FromInt(UISeeds)));
}

void UFPSUserWidget::IncreaseWaterText(int amount)
{
	if (!WaterText) return;

	UIWater = FMath::Min(UIWater + amount, 10);
	WaterText->SetText(FText::FromString(FString::Printf(TEXT("Water: %d"), UIWater)));

	if (!WaterBar) return;

	WaterBar->SetPercent(UIWater / 10.0f);
}

void UFPSUserWidget::DecreaseWaterText(int amount)
{
	if (!WaterText) return;

	UIWater = FMath::Max(0, UIWater - amount);
	WaterText->SetText(FText::FromString(FString::Printf(TEXT("Water: %d"), UIWater)));

	if (!WaterBar) return;

	WaterBar->SetPercent(UIWater / 10.0f);
}


