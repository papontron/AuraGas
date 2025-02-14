// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "AttributeSet.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	/*Primary Attributes*/
	OnStrengthChanged.Broadcast(AuraAttributeSet->GetStrength());
	OnResilienceChanged.Broadcast(AuraAttributeSet->GetResilience());
	OnIntelligenceChanged.Broadcast(AuraAttributeSet->GetIntelligence());
	OnVigorChanged.Broadcast(AuraAttributeSet->GetVigor());
	/*End Primary Attributes*/
	/*Secondary Attributes*/
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	OnMaxStaminaChanged.Broadcast(AuraAttributeSet->GetMaxStamina());
	/*End Secondary Attributes*/
	/*Vital Attributes*/
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnStaminaChanged.Broadcast(AuraAttributeSet->GetStamina());
	/*End Vital Attributes*/
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	/*Primary Attributes*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetStrengthAttribute()).AddLambda([this]
		(const FOnAttributeChangeData &Data)
	{
		OnStrengthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetResilienceAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{
		OnResilienceChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetIntelligenceAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{
		OnIntelligenceChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetVigorAttribute()).AddLambda([this](const FOnAttributeChangeData &Data)
	{
		OnVigorChanged.Broadcast(Data.NewValue);
	});
	/*End Primary Attributes*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda([this,AuraAttributeSet](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([this]
		(const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetStaminaAttribute()).AddUObject(this,&UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxStaminaChanged.Broadcast(Data.NewValue);
	});

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate.AddLambda([this](const FGameplayTagContainer &GameplayTagContainer)
	{
		for (const FGameplayTag &Tag: GameplayTagContainer)
		{
			
			// GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Magenta,FString::Printf(TEXT("Tag: %s"),*Tag.ToString()));
			FGameplayTag Message = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(Message))
			{
				FUIWidgetRow *Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}
