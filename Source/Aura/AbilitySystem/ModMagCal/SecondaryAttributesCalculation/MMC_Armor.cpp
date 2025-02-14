// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_Armor.h"

#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interactive/CombatInterface.h"

UMMC_Armor::UMMC_Armor()
{
	AgilityDefinition.AttributeToCapture = UAuraAttributeSet::GetAgilityAttribute();
	AgilityDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AgilityDefinition.bSnapshot = false;
	RelevantAttributesToCapture.Add(AgilityDefinition);
}

float UMMC_Armor::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	EvaluationParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const int32 CharacterLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetCharacterLevel();
	float Agility = 0;
	GetCapturedAttributeMagnitude(AgilityDefinition,Spec,EvaluationParams,Agility);
	Agility = FMath::Max(Agility,0);
	//10 points of agility grant 1 point of armor, and each level grant 2 of armor
	return 4+Agility/10+CharacterLevel*2;
}
