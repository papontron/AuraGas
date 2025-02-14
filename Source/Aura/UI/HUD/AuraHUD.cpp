// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/UI/HUD/AuraHUD.h"
#include "Aura/UI/Widget/AuraUserWidget.h"
#include "Aura/UI/WidgetController/OverlayWidgetController.h"
#include "Aura/UI/WidgetController/AttributeMenuWidgetController.h"
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	if (!AttributeMenuWidgetController)
	{
		return InitAttributeMenuWidgetController(WidgetControllerParams);
	}
	return AttributeMenuWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::InitAttributeMenuWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	
	if (!AttributeMenuWidgetController)
	{
		checkf(AttributeMenuWidgetControllerClass,TEXT("Attribute Menu Widget Controller Class must be specified!"));
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
		AttributeMenuWidgetController->BroadcastValues();
	}
	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget class is null"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller class is null"));
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	OverlayWidget->SetWidgetController(AAuraHUD::GetOverlayWidgetController(WidgetControllerParams));//ReceiveSetWidgetController has been called already at this point
	//broadcast initial values
	OverlayWidgetController->BindCallbacksToDependencies();
	OverlayWidgetController->BroadcastValues();
	
	OverlayWidget->AddToViewport();
}



