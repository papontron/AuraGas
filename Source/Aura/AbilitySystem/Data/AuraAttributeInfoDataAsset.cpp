// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAttributeInfoDataAsset.h"

FAuraAttributeInfo UAuraAttributeInfoDataAsset::FindTagAttributeInfo(const FGameplayTag& InAttributeTag,
	const bool bLogNotFound)
{
	for (const FAuraAttributeInfo& Row: AttributesInformation)
	{
		if (InAttributeTag.MatchesTagExact(Row.AttributeTag))
		{
			return Row;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute %s not found in %s."),*InAttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
