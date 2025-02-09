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
	FGameplayTag Attribute_Derived_IgnoreArmorChance;
	FGameplayTag Attribute_Derived_CriticalDamageChance;
	FGameplayTag Attribute_Derived_ExcellentDamageChance;
	FGameplayTag Attribute_Derived_CriticalDamage;
	FGameplayTag Attribute_Derived_ExcellentDamage;
	FGameplayTag Attribute_Derived_StunChance;
	FGameplayTag Attribute_Derived_DoubleDamageChance;
	FGameplayTag Attribute_Derived_TripleDamageChance;
	FGameplayTag Attribute_Derived_FreezeDebuff;
	FGameplayTag Attribute_Derived_BurnDebuff;
	FGameplayTag Attribute_Derived_PoisonDebuff;
	FGameplayTag Attribute_Derived_FreezeChance;
	FGameplayTag Attribute_Derived_BurnChance;
	FGameplayTag Attribute_Derived_PoisonChance;
	//MessageTags
	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaPotion;
	FGameplayTag Message_StaminaPotion;
	FGameplayTag Message_HealthCrystal;
	FGameplayTag Message_ManaCrystal;
	FGameplayTag Message_StaminaCrystal;
protected:
	void InitPrimaryAttributesTags();
	void InitSecondaryAttributesTags();
	void InitDerivedAttributesTags();
	void InitVitalAttributesTags();
	void InitMessageTags();
private:
	static FAuraGameplayTags GameplayTags;
};



