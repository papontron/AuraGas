// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemComponent.h"

#include "Aura/AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{	
	//const FGameplayTagContainer TagContainer = GameplayEffectSpec.Def.Get()->GetGrantedTags(); //GameplayEffectSpec.GetAllGrantedTags();
	
	FGameplayTagContainer AssetTagContainer;
	GameplayEffectSpec.GetAllAssetTags(AssetTagContainer);
	//broadcast the effect asset tags on every effect applied
	EffectAssetTags.Broadcast(AssetTagContainer);
}
