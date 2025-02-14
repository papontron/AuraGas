// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Aura/Interactive/CombatInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class USpringArmComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UCameraComponent;
UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();
	USkeletalMeshComponent* GetWeapon();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	void SetAbilitySystemComponent(UAbilitySystemComponent* InAbilitySystemComponent);
	void SetAttributeSet(UAttributeSet* InAttributeSet);

protected:
	
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere,Category="Setup")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(BlueprintReadWrite, Category="Setup")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite, Category="Setup")
	UAttributeSet* AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DefaultAttributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DefaultAttributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="DefaultAttributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UFUNCTION()
	void InitAllAttributes() const;
	
	UFUNCTION()
	void InitPrimaryAttributes() const;
	UFUNCTION()
	void InitSecondaryAttributes() const;
	UFUNCTION()
	void InitVitalAttributes() const;

	//grants the start up character's abilities
	void GrantStartUpAbilities() const;

	UPROPERTY(EditAnywhere,Category="Setup")
	FName WeaponTipSocketName;

	virtual FVector GetCombatSocketLocation() const override;
private:
	
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> &GameplayEffectClass,const float ActorLevel) const;
	
	UPROPERTY(EditAnywhere, Category="Abilities/StartUp", meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	
};

 
