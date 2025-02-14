// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInputTagDataAsset.generated.h"
class UInputAction;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FAbilityInputTag
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AbilityInputAction = nullptr;
};
/**
 * 
 */
UCLASS(Blueprintable)
class AURA_API UAbilityInputTagDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UInputAction* GetAbilityInputActionByTag(const FGameplayTag &AbilityTag, bool bLogError);
	UPROPERTY(EditDefaultsOnly,BLueprintReadOnly, Category = "Setup", meta=(AllowPrivateAccess=true))
	TArray<FAbilityInputTag> AbilityInputTags;
};
