// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_MagicalDamage.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_MagicalDamage::UMMC_MagicalDamage()
{
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

float UMMC_MagicalDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float Intelligence = 0;
	GetCapturedAttributeMagnitude(IntelligenceDefinition,Spec,EvaluateParameters,Intelligence);
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel();
	Intelligence = FMath::Max(Intelligence,0);
	return 40*Intelligence*2.4+CharacterLevel*12;
}
