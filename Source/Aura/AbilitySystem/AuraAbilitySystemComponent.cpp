// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/AuraGameplayAbility.h"
#include "Aura/AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);
}

void UAuraAbilitySystemComponent::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant) 
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : AbilitiesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		if (const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			//DynamicAbilityTags
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraGameplayAbility->StartupInputTag);
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::Printf(TEXT("StartupInputTag added: %s"),*AuraGameplayAbility->StartupInputTag.GetTagName().ToString()));
			GiveAbility(AbilitySpec);
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan, FString::Printf(TEXT("Ability Granted: %s"),*AbilitySpec.Ability.GetName()));
		}
		// this one doesn't activate the ability
		//GiveAbilityAndActivateOnce(AbilitySpec); 
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag &Tag)
{
	if (!Tag.IsValid()) return;
	for (auto &AbilitySpec :GetActivatableAbilities())
	{
		//GEngine->AddOnScreenDebugMessage(-1,4.f,FColor::Silver, FString::Printf(TEXT("Looping Available abilities: %s"), *AbilitySpec.Ability.GetName()));
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			//turn the flag on: The input is being pressed of this ability
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
				//GEngine->AddOnScreenDebugMessage(-1,4.f,FColor::Black, FString::Printf(TEXT("Ability Activated: %s"), *AbilitySpec.Ability.GetName()));
			}
		}
		
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag &Tag)
{
	if (!Tag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

//broadcasts all the asset tag container of every gamepleay effect that is applied
void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(
	UAbilitySystemComponent* AbilitySystemComponent,
    const FGameplayEffectSpec& GameplayEffectSpec,
    FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{	
	//const FGameplayTagContainer TagContainer = GameplayEffectSpec.Def.Get()->GetGrantedTags(); //GameplayEffectSpec.GetAllGrantedTags();
	
	FGameplayTagContainer AssetTagContainer;
	GameplayEffectSpec.GetAllAssetTags(AssetTagContainer);
	//broadcast the effect asset tags on every effect applied
	EffectAssetTagsDelegate.Broadcast(AssetTagContainer);
}
