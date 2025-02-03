﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Aura/Interactive/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraEnemy();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HighlightUnhighlight() override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void InitAbilityActorInfo() override;
	

};
