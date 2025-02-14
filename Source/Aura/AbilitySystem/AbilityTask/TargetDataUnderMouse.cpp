// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/AbilitySystem/AbilityTask/TargetDataUnderMouse.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
}