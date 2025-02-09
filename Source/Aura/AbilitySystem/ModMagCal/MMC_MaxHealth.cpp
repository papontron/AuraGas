// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/AbilitySystem/ModMagCal/MMC_MaxHealth.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	//In this case we are calculating one attribute (max health) based on other attribute both from the same character
	//so Target or Source comes to be the same
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot = false; // is capturing the attribute as soon as the gameplay effect is created
	
	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDefinition,Spec,EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor,0.f);
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 CharacterLevel = CombatInterface->GetCharacterLevel();
	
	return  80+4*Vigor+20*CharacterLevel;
}
