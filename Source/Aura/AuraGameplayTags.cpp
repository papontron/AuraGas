// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

//static variable
FAuraGameplayTags FAuraGameplayTags::GameplayTags;
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.InitPrimaryAttributesTags();
	GameplayTags.InitSecondaryAttributesTags();
	GameplayTags.InitDerivedAttributesTags();
	GameplayTags.InitVitalAttributesTags();
	GameplayTags.InitMessageTags();
}

void FAuraGameplayTags::InitPrimaryAttributesTags()
{
	Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString("Increases physical damage, critical&excellent damage and stun chance"));
	Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"),FString("Increases magical damage, max mana, mana regeneration and magical debuffs"));
	Attribute_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Agility"),FString("Increases the player's max movement speed and chances to apply critical&excellent damage and magical debuffs"));
	Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilience"),FString("Increases armor, armor penetration, and armor derived attributes"));
	Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"), FString("Increases max health, health regeneration, max stamina and stamina regeneration"));
}

void FAuraGameplayTags::InitSecondaryAttributesTags()
{
	Attribute_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.PhysicalDamage"),FString("Increases the player's damage when using weaponry"));
	Attribute_Secondary_MagicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MagicalDamage"),FString("Increases the player's damage when using sorcery"));
	Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("Reduces the damage taken"));
	Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"), FString("Reduces the enemy's armor and increases the chance to ignore all the enemy's armor"));
	Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString("Increases the player's health capacity"));
	Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString("Increases the player's mana capacity"));
	Attribute_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxStamina"), FString("Increases the player's stamina capacity"));
	Attribute_Secondary_HealthRegenerationRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegenerationRate"),FString("Increases the player's health regeneration per second"));
	Attribute_Secondary_ManaRegenerationRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegenerationRate"), FString("Increases the player's mana regeneration per second"));
	Attribute_Secondary_StaminaRegenerationRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.StaminaRegenerationRate"),FString("Increases the player's stamina regeneration per second"));
}

void FAuraGameplayTags::InitDerivedAttributesTags()
{
	Attribute_Derived_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.BlockChance"),FString("Chance to block completely an incoming attack"));
	Attribute_Derived_IgnoreArmorChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.IgnoreArmorChance"),FString("Change to ignore completely the enemy's armor in an attack"));
	Attribute_Derived_CriticalDamageChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.CriticalDamageChance"), FString("Chance to apply additional critical bonus damage upon an attack")); 
	Attribute_Derived_ExcellentDamageChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.ExcellentDamageChance"),FString("Change to apply additional excellent bonus damage upon an attack"));
	Attribute_Derived_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.CriticalDamage"),FString("The amount of bonus damaged to be applied upon a critical hit"));
	Attribute_Derived_ExcellentDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.ExcellentDamage"),FString("The amount of bonus damage to be applied upon an excellent hit"));
	Attribute_Derived_StunChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.StunChance"),FString("Chance to stun an enemy when applying physical damage"));
	Attribute_Derived_DoubleDamageChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.DoubleDamageChance"),FString("Chance to apply double damage")); 
	Attribute_Derived_TripleDamageChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.TripleDamageChance"),FString("Chance to apply triple damage"));
	Attribute_Derived_FreezeDebuff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.FreezeDebuff"), FString("A debuff that reduces the enemy's max movement speed"));
	Attribute_Derived_BurnDebuff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.BurnDebuff"),FString("A debuff that applies damage over time to the enemy"));
	Attribute_Derived_PoisonDebuff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.PoisonDebuff"),FString("A debuff the decreases the enemy's health regeneration"));
	Attribute_Derived_FreezeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.FreezeChance"),FString("Chance to apply FreezeDebuff"));
	Attribute_Derived_BurnChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.BurnChance"),FString("Chance to apply BurnDefuff"));
	Attribute_Derived_PoisonChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Derived.PoisonChance"),FString("Chance to apply PoisonDefuff"));
}

void FAuraGameplayTags::InitVitalAttributesTags()
{
	Attribute_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Health"),FString("The amount of damage a player can take before death"));
	Attribute_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Mana"),FString("Points required to cast sorcery or spells"));
	Attribute_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Stamina"),FString("Points required to sprint"));
}

void FAuraGameplayTags::InitMessageTags()
{
	Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"));
	Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"));
	Message_StaminaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.StaminaPotion"));
	Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"));
	Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"));
	Message_StaminaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.StaminaCrystal"));
}
