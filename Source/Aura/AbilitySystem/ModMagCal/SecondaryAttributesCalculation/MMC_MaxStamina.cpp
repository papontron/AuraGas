// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/AbilitySystem/ModMagCal/SecondaryAttributesCalculation/MMC_MaxStamina.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_MaxStamina::UMMC_MaxStamina()
{
	StrengthDefinition.AttributeToCapture = UAuraAttributeSet::GetStrengthAttribute();
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	ResilienceDefinition.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();

	StrengthDefinition.bSnapshot = false;
	IntelligenceDefinition.bSnapshot = false;
	ResilienceDefinition.bSnapshot = false;
	VigorDefinition.bSnapshot = false;

	StrengthDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(StrengthDefinition);
	RelevantAttributesToCapture.Add(IntelligenceDefinition);
	RelevantAttributesToCapture.Add(ResilienceDefinition);
	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float Strength= 0;
	float Intelligence = 0;
	float Resilience = 0;
	float Vigor = 0;
	GetCapturedAttributeMagnitude(StrengthDefinition,Spec,EvaluationParams,Strength);
	GetCapturedAttributeMagnitude(IntelligenceDefinition,Spec,EvaluationParams,Intelligence);
	GetCapturedAttributeMagnitude(ResilienceDefinition,Spec,EvaluationParams,Resilience);
	GetCapturedAttributeMagnitude(VigorDefinition,Spec,EvaluationParams,Vigor);
	Strength = FMath::Max<float>(Strength,0);
	Intelligence = FMath::Max<float>(Intelligence,0);
	Resilience = FMath::Max<float>(Resilience,0);
	Vigor = FMath::Max<float>(Vigor,0);
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel();
	return 20+Strength*1.2+Intelligence*0.5+Resilience*1.8+Vigor*2+CharacterLevel*10;
}
