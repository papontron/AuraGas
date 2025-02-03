// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"

#include <iostream>
#include <ostream>

#include "AbilitySystemBlueprintLibrary.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		
		TArray<FActiveGameplayEffectHandle> ActiveGameplayEffects;
		for (TSubclassOf<UGameplayEffect> GameplayEffectClass : GameplayEffectClasses)
		{
			check(GameplayEffectClass);
			FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
			ContextHandle.AddSourceObject(this);
			FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,LevelActor,ContextHandle);
			const FGameplayEffectSpec GameplayEffectSpec = *GameplayEffectSpecHandle.Data.Get();
		
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(GameplayEffectSpec);
			GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Green,
				FString::Printf(TEXT("GameplayEffect Added, Source Address: %p"),this));
			bool bIsInfinite =GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
			if (bIsInfinite&& InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
			{
				
				ActiveGameplayEffects.Add(ActiveGameplayEffectHandle);
			}
		}
		
		ActiveGameplayEffectsMap.Add(this,ActiveGameplayEffects);
		
	}
	// if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(TargetActor))
	// {
	// 	
	// 	
	// 	
	// }
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
	int* myInt = nullptr;
	
	if (InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		
		for (auto KeyValuePair: ActiveGameplayEffectsMap)
		{
			if (KeyValuePair.Key == this)
			{
				//remove all the gameplay effects applied by this actor
				for (auto ActiveGameplayEffect: KeyValuePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(ActiveGameplayEffect);
					GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Green,
				FString::Printf(TEXT("GameplayEffect Removed, Source Address: %p"),this));
				}
			}
		}
		
		ActiveGameplayEffectsMap.FindAndRemoveChecked(this);
		
	}
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}




