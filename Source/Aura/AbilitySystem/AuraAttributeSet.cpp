// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Aura/AuraGameplayTags.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& AuraGameplayTags = FAuraGameplayTags::Get();
	BindPrimaryAttributesToTags(AuraGameplayTags);
	BindSecondaryAttributesToTags(AuraGameplayTags);
	BindDerivedAttributesToTags(AuraGameplayTags);
	BindVitalAttributesToTags(AuraGameplayTags);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Stamina,COND_None,REPNOTIFY_Always);
	
	//Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Agility,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxStamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,PhysicalDamage,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//epic recommends to use this function only to do clamping
	//because it only returns the result from querying the modifier,
	//which means that this calculation will be made again by other effects with his own modifiers
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
	//GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Blue, FString::Printf(TEXT("Magnitude: %f"),Data.EvaluatedData.Magnitude));
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
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

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}

void UAuraAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Agility,OldAgility);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience,OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_MagicalDamage(const FGameplayAttributeData& OldMagicalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MagicalDamage,OldMagicalDamage);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,StaminaRegeneration, OldStaminaRegeneration);
}

void UAuraAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,PhysicalDamage,OldPhysicalDamage);
}


void UAuraAttributeSet::OnRep_BurnChance(const FGameplayAttributeData& OldBurnChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BurnChance, OldBurnChance);
}

void UAuraAttributeSet::OnRep_BurnDebuff(const FGameplayAttributeData& OldBurnDebuff) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BurnDebuff, OldBurnDebuff);
}

void UAuraAttributeSet::OnRep_BurnResistance(const FGameplayAttributeData& OldBurnResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BurnResistance, OldBurnResistance);
}

void UAuraAttributeSet::OnRep_FreezeResistance(const FGameplayAttributeData& OldFreezeResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FreezeResistance, OldFreezeResistance);
}

void UAuraAttributeSet::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PoisonResistance, OldPoisonResistance);
}

void UAuraAttributeSet::OnRep_FreezeChance(const FGameplayAttributeData& OldFreezeChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FreezeChance, OldFreezeChance);
}

void UAuraAttributeSet::OnRep_FreezeDebuff(const FGameplayAttributeData& OldFreezeDebuff) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FreezeDebuff, OldFreezeDebuff);
}

void UAuraAttributeSet::OnRep_PoisonChance(const FGameplayAttributeData& OldPoisonChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PoisonChance, OldPoisonChance);
}

void UAuraAttributeSet::OnRep_PoisonDebuff(const FGameplayAttributeData& OldPoisonDebuff) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PoisonDebuff, OldPoisonDebuff);
}

void UAuraAttributeSet::OnRep_ExcellentHitChance(const FGameplayAttributeData& OldExcellentHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ExcellentHitChance, OldExcellentHitChance);
}

void UAuraAttributeSet::OnRep_ExcellentHitDamage(const FGameplayAttributeData& OldExcellentHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ExcellentHitDamage, OldExcellentHitDamage);
}

void UAuraAttributeSet::OnRep_ExcellentHitResistance(const FGameplayAttributeData& OldExcellentHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ExcellentHitResistance, OldExcellentHitResistance);
}
void UAuraAttributeSet::OnRep_DoubleDamageHitChance(const FGameplayAttributeData& OldDoubleDamageHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,DoubleDamageHitChance, OldDoubleDamageHitChance);
}

void UAuraAttributeSet::OnRep_DoubleDamageHitResistance(const FGameplayAttributeData& OldDoubleDamageHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,DoubleDamageHitResistance, OldDoubleDamageHitResistance);
}

void UAuraAttributeSet::OnRep_TripleDamageHitChance(const FGameplayAttributeData& OldTripleDamageHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,TripleDamageHitChance, OldTripleDamageHitChance);
}

void UAuraAttributeSet::OnRep_TripleDamageHitResistance(const FGameplayAttributeData& OldTripleDamageHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,TripleDamageHitResistance, OldTripleDamageHitResistance);
}

void UAuraAttributeSet::OnRep_IgnoreArmorHitChance(const FGameplayAttributeData& OldIgnoreArmorHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,IgnoreArmorHitChance, OldIgnoreArmorHitChance);
}

void UAuraAttributeSet::OnRep_IgnoreArmorHitResistance(const FGameplayAttributeData& OldIgnoreArmorHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,IgnoreArmorHitResistance, OldIgnoreArmorHitResistance);
}

void UAuraAttributeSet::OnRep_StunHitChance(const FGameplayAttributeData& OldStunHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,StunHitChance, OldStunHitChance);
}

void UAuraAttributeSet::OnRep_StunHitResistance(const FGameplayAttributeData& OldStunHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,StunHitResistance, OldStunHitResistance);
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
			if (const APawn* SourcePawn = Cast<APawn>(EffectProperties.SourceData.AvatarActor))
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

void UAuraAttributeSet::BindPrimaryAttributesToTags(const FAuraGameplayTags& AuraGameplayTags)
{
	PrimaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Primary_Strength,GetStrengthAttribute);
	PrimaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Primary_Agility,GetAgilityAttribute);
	PrimaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Primary_Resilience,GetResilienceAttribute);
	PrimaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Primary_Intelligence,GetIntelligenceAttribute);
	PrimaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Primary_Vigor,GetVigorAttribute);
}

void UAuraAttributeSet::BindSecondaryAttributesToTags(const FAuraGameplayTags& AuraGameplayTags)
{
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_Armor,GetArmorAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_MagicalDamage,GetMagicalDamageAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_MaxHealth,GetMaxHealthAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_MaxMana,GetMaxManaAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_MaxStamina,GetMaxStaminaAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_PhysicalDamage,GetPhysicalDamageAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_HealthRegenerationRate,GetHealthRegenerationAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_ManaRegenerationRate,GetManaRegenerationAttribute);
	SecondaryTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Secondary_StaminaRegenerationRate,GetStaminaRegenerationAttribute);
}

void UAuraAttributeSet::BindDerivedAttributesToTags(const FAuraGameplayTags& AuraGameplayTags)
{
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_BlockChance,GetBlockChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_BurnChance,GetBurnChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_BurnDebuff,GetBurnDebuffAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_BurnResistance,GetBurnResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_FreezeChance,GetFreezeChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_FreezeDebuff,GetFreezeDebuffAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_FreezeResistance,GetFreezeResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_PoisonChance,GetPoisonChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_PoisonDebuff,GetPoisonDebuffAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_PoisonResistance,GetPoisonResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_CriticalHitChance,GetCriticalHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_CriticalHitDamage,GetCriticalHitDamageAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_CriticalHitResistance,GetCriticalHitResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_ExcellentHitChance,GetExcellentHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_ExcellentHitDamage,GetExcellentHitDamageAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_ExcellentHitResistance,GetExcellentHitResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_DoubleDamageHitChance,GetDoubleDamageHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_DoubleDamageHitResistance,GetDoubleDamageHitResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_TripleDamageHitChance,GetTripleDamageHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_TripleDamageHitResistance,GetTripleDamageHitResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_IgnoreArmorHitChance,GetIgnoreArmorHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_IgnoreArmorHitResistance,GetIgnoreArmorHitResistanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_StunHitChance,GetStunHitChanceAttribute);
	DerivedTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Derived_StunHitResistance,GetStunHitResistanceAttribute);
}

void UAuraAttributeSet::BindVitalAttributesToTags(const FAuraGameplayTags& AuraGameplayTags)
{
	VitalTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Vital_Health,GetHealthAttribute);
	VitalTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Vital_Mana,GetManaAttribute);
	VitalTagsToAttributesMap.Add(AuraGameplayTags.Attribute_Vital_Stamina,GetStaminaAttribute);
}
