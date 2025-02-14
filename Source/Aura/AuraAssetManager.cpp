// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

const UAuraAssetManager& UAuraAssetManager::Get()
{
	checkf(GEngine,TEXT("GameEngine couldn't be loaded"));
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//create all the gameplay tags that this game carries on (natively)
	FAuraGameplayTags::InitializeNativeGameplayTags();
	//Dont forget to set AssetManagerClassName=/Script/Aura.AuraAssetManager in the
	//DefaultEngine config file under the[/Script/Engine.Engine] section
}
