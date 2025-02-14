// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/AbilitySystem/ModMagCal/SecondaryAttributesCalculation/MMC_MaxMana.h"
#include "Aura/Interactive/CombatInterface.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}


float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float Intelligence = 0;
	GetCapturedAttributeMagnitude(IntelligenceDefinition,Spec,EvaluationParams,Intelligence);
	//can not be lower than 0
	Intelligence = FMath::Max<float>(Intelligence,0);
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel(); 
	return 60+Intelligence*5+10*CharacterLevel;
}
