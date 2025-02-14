// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
// typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FGameplayAttributeFuncPtr; 
// template <class T>
// using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

struct FAuraGameplayTags;
struct FGameplayEffectData
{
	UAbilitySystemComponent* AbilitySystemComponent;
	AActor* AvatarActor;
	ACharacter* Character;
	AController* Controller;
};
struct FEffectProperties
{
	FGameplayEffectContextHandle ContextHandle;
	FGameplayEffectData SourceData;
	FGameplayEffectData TargetData;
};
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//Begin Primary Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="PrimaryAttributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData &OldStrength) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Agility,Category="PrimaryAttributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Agility);
	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData &OldAgility) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence, Category = "PrimaryAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData &OldIntelligence) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Resilience, Category = "PrimaryAttributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData &OldResilience) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Vigor, Category="PrimaryAttributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData &OldVigor) const;
	
	//End Primary Attributes

	/*
	 * Secondary Attributes(these attributes depend on other attributes)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category="SecondaryAttributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData &OldArmor) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenetration, Category="SecondaryAttributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData &OldArmorPenetration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MagicalDamage, Category="SecondaryAttributes")
	FGameplayAttributeData MagicalDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MagicalDamage);
	UFUNCTION()
	void OnRep_MagicalDamage(const FGameplayAttributeData& OldMagicalDamage) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegeneration, Category="SecondaryAttributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData &OldHealthRegeneration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegeneration, Category="SecondaryAttributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData &OldManaRegeneration) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_StaminaRegeneration, Category="SecondaryAttributes")
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaminaRegeneration);
	UFUNCTION()
	void OnRep_StaminaRegeneration(const FGameplayAttributeData &OldStaminaRegeneration) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth, Category="SecondaryAttributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana, Category="SecondaryAttributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxStamina, Category="SecondaryAttributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStamina);
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PhysicalDamage,Category="SecondaryAttributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalDamage);
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData &OldPhysicalDamage) const;
	
	/*
	 * End secondary Attributes
	 */

	/* Derived Attributes */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BlockChance, Category="DerivedAttributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData &OldBlockChance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BurnChance, Category="DerivedAttributes")
	FGameplayAttributeData BurnChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BurnChance);
	UFUNCTION()
	void OnRep_BurnChance(const FGameplayAttributeData &OldBurnChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BurnDebuff, Category="DerivedAttributes")
	FGameplayAttributeData BurnDebuff;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BurnDebuff);
	UFUNCTION()
	void OnRep_BurnDebuff(const FGameplayAttributeData &OldBurnDebuff) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BurnResistance,Category="DerivedAttributes")
	FGameplayAttributeData BurnResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BurnResistance);
	UFUNCTION()
	void OnRep_BurnResistance(const FGameplayAttributeData&OldBurnResistance) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_FreezeChance,Category="DerivedAttributes")
	FGameplayAttributeData FreezeChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FreezeChance);
	UFUNCTION()
	void OnRep_FreezeChance(const FGameplayAttributeData &OldFreezeChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_FreezeDebuff,Category="DerivedAttributes")
	FGameplayAttributeData FreezeDebuff;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FreezeDebuff);
	UFUNCTION()
	void OnRep_FreezeDebuff(const FGameplayAttributeData &OldFreezeDebuff) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_FreezeResistance,Category="DerivedAttributes")
	FGameplayAttributeData FreezeResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FreezeResistance);
	UFUNCTION()
	void OnRep_FreezeResistance(const FGameplayAttributeData& OldFreezeResistance) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PoisonChance,Category="DerivedAttributes")
	FGameplayAttributeData PoisonChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PoisonChance);
	UFUNCTION()
	void OnRep_PoisonChance(const FGameplayAttributeData &OldPoisonChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PoisonDebuff,Category="DerivedAttributes")
	FGameplayAttributeData PoisonDebuff;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PoisonDebuff);
	UFUNCTION()
	void OnRep_PoisonDebuff(const FGameplayAttributeData &OldPoisonDebuff) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PoisonResistance,Category="DerivedAttributes")
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PoisonResistance);
	UFUNCTION()
	void OnRep_PoisonResistance(const FGameplayAttributeData &OldPoisonResistance) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitChance, Category="DerivedAttributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData &OldCriticalChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitDamage, Category="DerivedAttributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData &OldCriticalHitDamage) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitResistance, Category="DerivedAttributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData &OldCriticalHitResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ExcellentHitChance, Category="DerivedAttributes")
	FGameplayAttributeData ExcellentHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ExcellentHitChance);
	UFUNCTION()
	void OnRep_ExcellentHitChance(const FGameplayAttributeData &OldExcellentHitChance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ExcellentHitDamage, Category="DerivedAttributes")
	FGameplayAttributeData ExcellentHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ExcellentHitDamage);
	UFUNCTION()
	void OnRep_ExcellentHitDamage(const FGameplayAttributeData &OldExcellentHitDamage) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ExcellentHitResistance, Category="DerivedAttributes")
	FGameplayAttributeData ExcellentHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ExcellentHitResistance);
	UFUNCTION()
	void OnRep_ExcellentHitResistance(const FGameplayAttributeData& OldExcellentHitResistance)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_DoubleDamageHitChance)
	FGameplayAttributeData DoubleDamageHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, DoubleDamageHitChance);
	UFUNCTION()
	void OnRep_DoubleDamageHitChance(const FGameplayAttributeData &OldDoubleDamageHitChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_DoubleDamageHitResistance)
	FGameplayAttributeData DoubleDamageHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, DoubleDamageHitResistance);
	UFUNCTION()
	void OnRep_DoubleDamageHitResistance(const FGameplayAttributeData &OldDoubleDamageHitResistance)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_TripleDamageHitChance)
	FGameplayAttributeData TripleDamageHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, TripleDamageHitChance);
	UFUNCTION()
	void OnRep_TripleDamageHitChance(const FGameplayAttributeData &OldTripleDamageHitChance)const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_TripleDamageHitResistance, Category="DerivedAttributes")
	FGameplayAttributeData TripleDamageHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, TripleDamageHitResistance);
	UFUNCTION()
	void OnRep_TripleDamageHitResistance(const FGameplayAttributeData &OldTripleDamageHitResistance)const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_IgnoreArmorHitChance,Category="DerivedAttributes")
	FGameplayAttributeData IgnoreArmorHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IgnoreArmorHitChance);
	UFUNCTION()
	void OnRep_IgnoreArmorHitChance(const FGameplayAttributeData &OldIgnoreArmorHitChance)const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_IgnoreArmorHitResistance, Category="DerivedAttributes")
	FGameplayAttributeData IgnoreArmorHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IgnoreArmorHitResistance);
	UFUNCTION()
	void OnRep_IgnoreArmorHitResistance(const FGameplayAttributeData &OldIgnoreArmorHitResistance)const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_StunHitChance,Category="DerivedAttributes")
	FGameplayAttributeData StunHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StunHitChance);
	UFUNCTION()
	void OnRep_StunHitChance(const FGameplayAttributeData &OldStunHitChance)const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_StunHitResistance,category="DerivedAttributes")
	FGameplayAttributeData StunHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StunHitResistance);
	UFUNCTION()
	void OnRep_StunHitResistance(const FGameplayAttributeData &OldStunHitResistance)const;
	/*End Derived Attributes*/
	
	//Vital Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health, Category="VitalAttributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &OldHealth) const;
	
	UPROPERTY(BlueprintReadonly,ReplicatedUsing=OnRep_Mana, category="VitalAttributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &OldMana) const;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Stamina, Category="VitalAttributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stamina);
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	//end vital attributes
	
	TMap<FGameplayTag, FGameplayAttribute(*)()> PrimaryTagsToAttributesMap;
	TMap<FGameplayTag, FGameplayAttribute(*)()> SecondaryTagsToAttributesMap;
	TMap<FGameplayTag, FGameplayAttribute(*)()> DerivedTagsToAttributesMap;
	TMap<FGameplayTag, FGameplayAttribute(*)()> VitalTagsToAttributesMap;
protected:
	void SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties& EffectProperties);
private:
	void BindPrimaryAttributesToTags(const FAuraGameplayTags& AuraGameplayTags);
	void BindSecondaryAttributesToTags(const FAuraGameplayTags& AuraGameplayTags);
	void BindDerivedAttributesToTags(const FAuraGameplayTags& AuraGameplayTags);
	void BindVitalAttributesToTags(const FAuraGameplayTags& AuraGameplayTags);
};



