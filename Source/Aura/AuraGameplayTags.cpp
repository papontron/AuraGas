// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

//static variable
FAuraGameplayTags FAuraGameplayTags::GameplayTags;
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	GameplayTags.InitPrimaryAttributesTags(GameplayTagsManager);
	GameplayTags.InitSecondaryAttributesTags(GameplayTagsManager);
	GameplayTags.InitDerivedAttributesTags(GameplayTagsManager);
	GameplayTags.InitVitalAttributesTags(GameplayTagsManager);
	GameplayTags.InitMessageTags(GameplayTagsManager);
	GameplayTags.InitAbilityInputTags(GameplayTagsManager);
}

void FAuraGameplayTags::InitPrimaryAttributesTags(UGameplayTagsManager &GameplayTagsManager)
{
	Attribute_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString("Increases physical damage, critical&excellent damage and stun chance"));
	Attribute_Primary_Intelligence = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"),FString("Increases magical damage, max mana, mana regeneration and magical debuffs"));
	Attribute_Primary_Agility = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Agility"),FString("Increases the player's max movement speed and chances to apply critical&excellent damage and magical debuffs"));
	Attribute_Primary_Resilience = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Resilience"),FString("Increases armor, armor penetration, and armor derived attributes"));
	Attribute_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Vigor"), FString("Increases max health, health regeneration, max stamina and stamina regeneration"));
}

void FAuraGameplayTags::InitSecondaryAttributesTags(UGameplayTagsManager &GameplayTagsManager)
{
	Attribute_Secondary_PhysicalDamage = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.PhysicalDamage"),FString("Increases the player's damage when using weaponry"));
	Attribute_Secondary_MagicalDamage = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MagicalDamage"),FString("Increases the player's damage when using sorcery"));
	Attribute_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("Reduces the damage taken"));
	Attribute_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"), FString("Reduces the enemy's armor and increases the chance to ignore all the enemy's armor"));
	Attribute_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString("Increases the player's health capacity"));
	Attribute_Secondary_MaxMana = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString("Increases the player's mana capacity"));
	Attribute_Secondary_MaxStamina = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MaxStamina"), FString("Increases the player's stamina capacity"));
	Attribute_Secondary_HealthRegenerationRate = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegenerationRate"),FString("Increases the player's health regeneration per second"));
	Attribute_Secondary_ManaRegenerationRate = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegenerationRate"), FString("Increases the player's mana regeneration per second"));
	Attribute_Secondary_StaminaRegenerationRate = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.StaminaRegenerationRate"),FString("Increases the player's stamina regeneration per second"));
}

void FAuraGameplayTags::InitDerivedAttributesTags(UGameplayTagsManager &GameplayTagsManager)
{
	Attribute_Derived_BlockChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.BlockChance"),FString("Chance to block completely an incoming attack"));
	Attribute_Derived_IgnoreArmorHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.IgnoreArmorHitChance"),FString("Change to ignore completely the enemy's armor in an attack"));
	Attribute_Derived_IgnoreArmorHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.IgnoreArmorHitResistance"),FString("Reduces the chance to get your armor ignored in an attack"));
	Attribute_Derived_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.CriticalDamageHitChance"), FString("Chance to apply additional critical bonus damage upon an attack")); 
	Attribute_Derived_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.CriticalHitDamage"),FString("The amount of bonus damaged to be applied upon a critical hit"));
	Attribute_Derived_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.CriticalHitResistance"),FString("Reduces to chance to get a critical hit"));
	Attribute_Derived_ExcellentHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.ExcellentDamageHitChance"),FString("Change to apply additional excellent bonus damage upon an attack"));
	Attribute_Derived_ExcellentHitDamage = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.ExcellentHitDamage"),FString("The amount of bonus damage to be applied upon an excellent hit"));
	Attribute_Derived_ExcellentHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.ExcellentHitResistance"),FString("Reduces the chance to get an excellent hit"));
	Attribute_Derived_StunHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.StunHitChance"),FString("Chance to stun an enemy when applying physical damage"));
	Attribute_Derived_StunHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.StunHitResistance"),FString("Reduces the chance to be stunned"));
	Attribute_Derived_DoubleDamageHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.DoubleDamageHitChance"),FString("Chance to apply double damage"));
	Attribute_Derived_DoubleDamageHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.DoubleDamageHitResistance"),FString("Reduces the chance to receive a double damage hit"));
	Attribute_Derived_TripleDamageHitChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.TripleDamageHitChance"),FString("Chance to apply triple damage"));
	Attribute_Derived_TripleDamageHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.TripleDamageHitResistance"),FString("Reduces the chance to receive a triple damage hit"));
	Attribute_Derived_FreezeDebuff = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.FreezeDebuff"), FString("A debuff that reduces the enemy's max movement speed"));
	Attribute_Derived_FreezeChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.FreezeChance"),FString("Chance to apply FreezeDebuff"));
	Attribute_Derived_FreezeResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.FreezeResistance"),FString("Reduces the chance to be frozen"));
	Attribute_Derived_BurnDebuff = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.BurnDebuff"),FString("A debuff that applies damage over time to the enemy"));
	Attribute_Derived_BurnChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.BurnChance"),FString("Chance to apply BurnDefuff"));
	Attribute_Derived_BurnResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.BurnResistance"),FString("Reduces the chance to be burned"));
	Attribute_Derived_PoisonDebuff = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.PoisonDebuff"),FString("A debuff the decreases the enemy's health regeneration"));
	Attribute_Derived_PoisonChance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.PoisonChance"),FString("Chance to apply PoisonDefuff"));
	Attribute_Derived_PoisonResistance = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Derived.PoisonResistance"),FString("Reduces the chance to be poisoned"));
}

void FAuraGameplayTags::InitVitalAttributesTags(UGameplayTagsManager &GameplayTagsManager)
{
	Attribute_Vital_Health = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Vital.Health"),FString("The amount of damage a player can take before death"));
	Attribute_Vital_Mana = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Vital.Mana"),FString("Points required to cast sorcery or spells"));
	Attribute_Vital_Stamina = GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Vital.Stamina"),FString("Points required to sprint"));
}

void FAuraGameplayTags::InitMessageTags(UGameplayTagsManager &GameplayTagsManager)
{
	Message_HealthPotion = GameplayTagsManager.AddNativeGameplayTag(FName("Message.HealthPotion"));
	Message_ManaPotion = GameplayTagsManager.AddNativeGameplayTag(FName("Message.ManaPotion"));
	Message_StaminaPotion = GameplayTagsManager.AddNativeGameplayTag(FName("Message.StaminaPotion"));
	Message_HealthCrystal = GameplayTagsManager.AddNativeGameplayTag(FName("Message.HealthCrystal"));
	Message_ManaCrystal = GameplayTagsManager.AddNativeGameplayTag(FName("Message.ManaCrystal"));
	Message_StaminaCrystal = GameplayTagsManager.AddNativeGameplayTag(FName("Message.StaminaCrystal"));
}

void FAuraGameplayTags::InitAbilityInputTags(UGameplayTagsManager& GameplayTagsManager)
{
	Input_Ability_LMB = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.LMB"), FString("Left mouse button"));
	Input_Ability_RMB = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.RMB"), FString("Right mouse button"));
	Input_Ability_CMB = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.CMB"), FString("Central mouse button"));
	Input_Ability_1 = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.1"), FString("Key 1"));
	Input_Ability_2 = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.2"), FString("Key 2"));
	Input_Ability_3 = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.3"), FString("Key 3"));
	Input_Ability_4 = GameplayTagsManager.AddNativeGameplayTag(FName("Input.Ability.4"), FString("Key 4"));
}
