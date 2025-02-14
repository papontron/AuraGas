// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_ArmorPenetration.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_ArmorPenetration::UMMC_ArmorPenetration()
{
	ResilienceDefinition.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDefinition.bSnapshot = false;
	RelevantAttributesToCapture.Add(ResilienceDefinition);
}

float UMMC_ArmorPenetration::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float Resilience = 0;
	GetCapturedAttributeMagnitude(ResilienceDefinition,Spec,EvaluateParameters,Resilience);
	Resilience = FMath::Max(Resilience,0);
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel();
	return (Resilience/12)+CharacterLevel*1;
}
