// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams &WidgetControllerParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	
};

