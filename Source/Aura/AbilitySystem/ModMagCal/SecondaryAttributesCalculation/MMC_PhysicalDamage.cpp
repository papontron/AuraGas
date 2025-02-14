// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_PhysicalDamage.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_PhysicalDamage::UMMC_PhysicalDamage()
{
	StrengthDefinition.AttributeToCapture = UAuraAttributeSet::GetStrengthAttribute();
	StrengthDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StrengthDefinition.bSnapshot = false;
	RelevantAttributesToCapture.Add(StrengthDefinition);
}

float UMMC_PhysicalDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float Strength = 0;
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel();
	GetCapturedAttributeMagnitude(StrengthDefinition,Spec,EvaluationParams,Strength);
	return 50+Strength*2+CharacterLevel*10;  
}
