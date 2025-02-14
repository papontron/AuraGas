// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityInputTagDataAsset.h"

UInputAction* UAbilityInputTagDataAsset::GetAbilityInputActionByTag(const FGameplayTag& AbilityTag, bool bLogError)
{
	for (const auto &AbilityInputTag : AbilityInputTags)
	{
		if (AbilityTag.MatchesTagExact(AbilityInputTag.AbilityTag)&& AbilityInputTag.AbilityInputAction)
		{
			
			return AbilityInputTag.AbilityInputAction;
		}
	}
	if (bLogError)
	{
		UE_LOG(LogTemp,Warning,TEXT("Unable to find an Ability Input Action for the Tag: %s"), *AbilityTag.ToString());
	}
	return nullptr;
}
