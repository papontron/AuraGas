// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTag, FGameplayTagContainer)
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	//this function will be called inmediately after the Ability actor info has been set
	void AbilityActorInfoSet();
	FEffectAssetTag EffectAssetTags;
protected:
	//this is function to be bind to the FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToSelf delegate
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
