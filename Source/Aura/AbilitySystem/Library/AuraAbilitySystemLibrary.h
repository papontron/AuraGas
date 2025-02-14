// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//BlueprintPure doesn't require an execution pin, it just performs a calculation and returns a value without changing any attribute
	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "AuraAbilitySystemLibrary|WidgetController")
	static const UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "AuraAbilitySystemLibrary|WidgetController")
	static const UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
