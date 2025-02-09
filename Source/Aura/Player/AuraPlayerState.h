// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChangeSignature, float, Level, bool, Changed);
/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps)const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const;

	int32 GetPlayerLevel() const;
	void SetPlayerLevel(const int32 NewLevel);
protected:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UAttributeSet* AttributeSet;
	UPROPERTY()
	FOnLevelChangeSignature OnLevelChangeDelegate;
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerLevel, Category="PlayerLevel")
	int32 PlayerLevel = 1;
	UFUNCTION()
	void OnRep_PlayerLevel(const int32& OldPlayerLevel);
	
};
