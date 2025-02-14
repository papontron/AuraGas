// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FAuraGameplayTags
{
	public:
	static const FAuraGameplayTags& Get() //returns a const reference
	{
		return GameplayTags;
	}
	static void InitializeNativeGameplayTags();
	
	//Primary Attributes Tags
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Agility;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Vigor;
	//Secondary Attributes Tags
	FGameplayTag Attribute_Secondary_PhysicalDamage;
	FGameplayTag Attribute_Secondary_MagicalDamage;
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
	FGameplayTag Attribute_Secondary_MaxStamina;
	FGameplayTag Attribute_Secondary_HealthRegenerationRate;
	FGameplayTag Attribute_Secondary_ManaRegenerationRate;
	FGameplayTag Attribute_Secondary_StaminaRegenerationRate;
	//Vital Attributes Tags
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;
	FGameplayTag Attribute_Vital_Stamina;
	//Derived Attributes Tags
	FGameplayTag Attribute_Derived_BlockChance;
	FGameplayTag Attribute_Derived_IgnoreArmorHitChance;
	FGameplayTag Attribute_Derived_IgnoreArmorHitResistance;
	FGameplayTag Attribute_Derived_CriticalHitChance;
	FGameplayTag Attribute_Derived_ExcellentHitChance;
	FGameplayTag Attribute_Derived_CriticalHitDamage;
	FGameplayTag Attribute_Derived_ExcellentHitDamage;
	FGameplayTag Attribute_Derived_StunHitChance;
	FGameplayTag Attribute_Derived_StunHitResistance;
	FGameplayTag Attribute_Derived_DoubleDamageHitChance;
	FGameplayTag Attribute_Derived_TripleDamageHitChance;
	FGameplayTag Attribute_Derived_FreezeDebuff;
	FGameplayTag Attribute_Derived_BurnDebuff;
	FGameplayTag Attribute_Derived_PoisonDebuff;
	FGameplayTag Attribute_Derived_FreezeChance;
	FGameplayTag Attribute_Derived_BurnChance;
	FGameplayTag Attribute_Derived_PoisonChance;
	FGameplayTag Attribute_Derived_CriticalHitResistance;
	FGameplayTag Attribute_Derived_ExcellentHitResistance;
	FGameplayTag Attribute_Derived_DoubleDamageHitResistance;
	FGameplayTag Attribute_Derived_TripleDamageHitResistance;
	FGameplayTag Attribute_Derived_FreezeResistance;
	FGameplayTag Attribute_Derived_BurnResistance;
	FGameplayTag Attribute_Derived_PoisonResistance;
	//MessageTags
	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaPotion;
	FGameplayTag Message_StaminaPotion;
	FGameplayTag Message_HealthCrystal;
	FGameplayTag Message_ManaCrystal;
	FGameplayTag Message_StaminaCrystal;
	//Ability inputs
	FGameplayTag Input_Ability_LMB;
	FGameplayTag Input_Ability_RMB;
	FGameplayTag Input_Ability_CMB;
	FGameplayTag Input_Ability_1;
	FGameplayTag Input_Ability_2;
	FGameplayTag Input_Ability_3;
	FGameplayTag Input_Ability_4;
protected:
	void InitPrimaryAttributesTags(UGameplayTagsManager &GameplayTagsManager);
	void InitSecondaryAttributesTags(UGameplayTagsManager &GameplayTagsManager);
	void InitDerivedAttributesTags(UGameplayTagsManager &GameplayTagsManager);
	void InitVitalAttributesTags(UGameplayTagsManager &GameplayTagsManager);
	void InitMessageTags(UGameplayTagsManager &GameplayTagsManager);
	void InitAbilityInputTags(UGameplayTagsManager &GameplayTagsManager);
private:
	static FAuraGameplayTags GameplayTags;
};



