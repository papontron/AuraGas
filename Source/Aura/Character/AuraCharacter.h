// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacter();
	/*CombatInterface*/
	virtual int32 GetCharacterLevel() override;
	/*End CombatInterface*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere,Category="Setup")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere,Category="Setup")
	TObjectPtr<USpringArmComponent> SpringArm;
};
