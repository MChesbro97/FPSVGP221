// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0f);
	IncreaseSeedsText(0);

	//if (ButtonWidgetPrefab) {
	//	for (int i = 0; i < 4; i++) {
	//		UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
	//		ButtonContainer->AddChild(widget);

	//		UButtonWidget* button = Cast<UButtonWidget>(widget); // Get Component in Unity
	//		button->SetText(i);
	//	}
	//}
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
