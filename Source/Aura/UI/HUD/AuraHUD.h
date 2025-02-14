// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
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
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams &WidgetControllerParams);
	UAttributeMenuWidgetController* InitAttributeMenuWidgetController(const FWidgetControllerParams &WidgetControllerParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	/*Overlay Widget*/
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	/*End Overlay Widget*/
	
	/*Overlay Widget Controller*/
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	/*End Overlay WidgetController*/

	/*AttributeMenuWidgetController*/
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	/*End AttributeMenuWidgetController*/
	
};

