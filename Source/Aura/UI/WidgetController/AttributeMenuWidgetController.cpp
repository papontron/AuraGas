// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeMenuWidgetController.h"
#include "Aura/AbilitySystem/Data/AuraAttributeInfoDataAsset.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	//bind lambdas to all attributes change delegates
	for (const auto & Pair: AuraAttributeSet->PrimaryTagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this,Pair](const FOnAttributeChangeData & Data)
		{
			BroadCastAttributeInfo(Pair.Key,Pair.Value(),PrimaryAttributeInfoDataAsset);
		});
	}
	for (const auto & Pair: AuraAttributeSet->SecondaryTagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this,Pair](const FOnAttributeChangeData & Data)
		{
			BroadCastAttributeInfo(Pair.Key,Pair.Value(),SecondaryAttributeInfoDataAsset);
		});
	}
	for (const auto & Pair: AuraAttributeSet->DerivedTagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this,Pair](const FOnAttributeChangeData & Data)
		{
			BroadCastAttributeInfo(Pair.Key,Pair.Value(),DerivedAttributeInfoDataAsset);
		});
	}
	for (const auto &Pair: AuraAttributeSet->VitalTagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this,Pair](const FOnAttributeChangeData & Data)
		{
			BroadCastAttributeInfo(Pair.Key,Pair.Value(),VitalAttributeInfoDataAsset);
		});
	}
}

void UAttributeMenuWidgetController::BroadcastValues()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	//Primary Attributes info
	for (const auto &Pair: AuraAttributeSet->PrimaryTagsToAttributesMap)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value(),PrimaryAttributeInfoDataAsset);
	}
	for (const auto &Pair: AuraAttributeSet->SecondaryTagsToAttributesMap)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value(),SecondaryAttributeInfoDataAsset);
	}
	for (const auto &Pair: AuraAttributeSet->DerivedTagsToAttributesMap)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value(),DerivedAttributeInfoDataAsset);
	}
	for (const auto &Pair: AuraAttributeSet->VitalTagsToAttributesMap)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value(),VitalAttributeInfoDataAsset);
	}
}

void UAttributeMenuWidgetController::BroadCastAttributeInfo(const FGameplayTag &Tag,const FGameplayAttribute &Attribute,UAuraAttributeInfoDataAsset *DataAsset) const
{
	FAuraAttributeInfo Info = DataAsset->FindTagAttributeInfo(Tag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
