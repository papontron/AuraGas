// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(100.f);
	InitMana(100.f);
	InitMaxHealth(200.f);
	InitMaxMana(200.f);
	InitStamina(100.f);
	InitMaxStamina(200.f);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Stamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxStamina,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//epic recommends to use this function only to do clamping
	Super::PreAttributeChange(Attribute, NewValue);
	if (GetHealthAttribute() == Attribute)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (GetManaAttribute() == Attribute)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
	if (Attribute == GetMaxStaminaAttribute() || Attribute == GetMaxHealthAttribute() || Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100000.f);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}
void UAuraAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Stamina,OldStamina);
}

void UAuraAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxStamina,OldMaxStamina);
}
void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties)
{
	//source Actor = causer of the effect, target actor = target of the effect
	EffectProperties.ContextHandle = Data.EffectSpec.GetContext();
	
	EffectProperties.SourceData.AbilitySystemComponent = EffectProperties.ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(EffectProperties.SourceData.AbilitySystemComponent)&&EffectProperties.SourceData.AbilitySystemComponent->AbilityActorInfo.IsValid()&&EffectProperties.SourceData.AbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceData.AvatarActor = EffectProperties.SourceData.AbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		
		AController* SourceController = EffectProperties.SourceData.AbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		EffectProperties.SourceData.Controller = SourceController;
		if (EffectProperties.SourceData.AvatarActor!=nullptr && SourceController==nullptr)
		{
			if (APawn* SourcePawn = Cast<APawn>(EffectProperties.SourceData.AvatarActor))
			{
				SourceController = SourcePawn->GetController();
			}
		}
		if (SourceController!=nullptr)
		{
			EffectProperties.SourceData.Character = SourceController->GetCharacter();
		}
	}
	//Target info:
	if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetData.AvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetData.Controller = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetData.Character = EffectProperties.TargetData.Controller->GetCharacter();
		EffectProperties.TargetData.AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetData.AvatarActor);		 
	}
}