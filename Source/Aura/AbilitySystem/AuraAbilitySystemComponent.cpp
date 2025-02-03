// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{	
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Magenta, FString::Printf(TEXT("Effect Applied: %s"), *GameplayEffectSpec.Def.Get()->GetName()));
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Magenta, FString::Printf(TEXT("Effect Applied: %s"), *GameplayEffectSpec.Def.Get()->GetGrantedTags().ToString()));
	const FGameplayTagContainer TagContainer = GameplayEffectSpec.Def.Get()->GetGrantedTags(); //GameplayEffectSpec.GetAllGrantedTags();
	
	FGameplayTagContainer AssetTagContainer;
	GameplayEffectSpec.GetAllAssetTags(AssetTagContainer);
	for (const FGameplayTag &Tag: TagContainer)
	{
		//TODO: Broadcast the tag to the blueprint widget controller
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString()));
	}
}
