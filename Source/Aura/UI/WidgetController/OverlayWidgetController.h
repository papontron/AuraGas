// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"
class UAuraUserWidget;
struct FOnAttributeChangeData;

USTRUCT(BLueprintType)
struct FUIWidgetRow: public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag GameplayTag;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UTexture2D> Image;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
//BLueprintType -> we can use it as type in blueprints( for example to perform casts)
//blueprintable-> we can make blueprints of this class
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetSignature, FUIWidgetRow, WidgetRow);

UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	/* Delegates */
	/* Primary Attributes Delegates */
	UPROPERTY(BlueprintAssignable,  Category = "GAS|Primary Attributes")
	FOnAttributeChangedSignature OnStrengthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Primary Attributes")
	FOnAttributeChangedSignature OnResilienceChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Primary Attributes")
	FOnAttributeChangedSignature OnIntelligenceChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Primary Attributes")
	FOnAttributeChangedSignature OnVigorChanged;
	/*End Primary Attributes Delegates*/
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnStaminaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Vital Attributes")
	FOnAttributeChangedSignature OnMaxStaminaChanged;
	UPROPERTY(BLueprintAssignable, Category = "GAS|Message Attributes")
	FMessageWidgetSignature MessageWidgetRowDelegate;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Message Widget")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
	void StaminaChanged(const FOnAttributeChangeData& Data);
	void MaxStaminaChanged(const FOnAttributeChangeData& Data);

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
