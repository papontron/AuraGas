// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Aura/AbilitySystem/AbilityInput/AbilityInputTagDataAsset.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindInputAbilityActions(UAbilityInputTagDataAsset* AbilityInputTagDataAsset, UserClass* ObjectReference, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindInputAbilityActions(UAbilityInputTagDataAsset* AbilityInputTagDataAsset,
	UserClass* ObjectReference, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	for (const FAbilityInputTag & AbilityInputTag: AbilityInputTagDataAsset->AbilityInputTags)
	{
		if (AbilityInputTag.AbilityInputAction && AbilityInputTag.AbilityTag.IsValid())
		{
			if (HeldFunc)
			{
				BindAction(AbilityInputTag.AbilityInputAction,ETriggerEvent::Triggered,ObjectReference, HeldFunc, AbilityInputTag.AbilityTag);
			}
			if (PressedFunc)
			{
				BindAction(AbilityInputTag.AbilityInputAction,ETriggerEvent::Started,ObjectReference, PressedFunc, AbilityInputTag.AbilityTag);
			}
			if (ReleasedFunc)
			{
				BindAction(AbilityInputTag.AbilityInputAction,ETriggerEvent::Completed,ObjectReference, ReleasedFunc, AbilityInputTag.AbilityTag);
			}
		}
	}
}
