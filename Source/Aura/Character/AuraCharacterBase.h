// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


class USpringArmComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UCameraComponent;
UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();
	USkeletalMeshComponent* GetWeapon();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	void SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent);
	void SetAttributeSet(UAttributeSet* AttributeSet);
protected:
	
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere,Category="Setup")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(BlueprintReadWrite, Category="Setup")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite, Category="Setup")
	UAttributeSet* AttributeSet; 
};

 
