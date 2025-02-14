// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataSignature, const FVector&, TargetData);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	//This is an asynchronous blueprint node
	//the way to add more output executions pins to this function is by broadcasting delegates
	UFUNCTION(BlueprintCallable,Category = "Ability|Tasks", meta=(DisplayName="TargetDataUnderMouse",HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly=true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);
	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature TargetDataDelegate;
};

 
