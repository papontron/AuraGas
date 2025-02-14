// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraProjectileSpell.h"

#include "Aura/Actor/AuraProjectile.h"
#include "Aura/Interactive/CombatInterface.h"
// #include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::SpawnProjectile()
{
	FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();
	checkf(ProjectileClass,TEXT("ProjectileClass must be a valid ProjectileClass"));
	bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;
	if (ICombatInterface* CombatInterface =Cast<ICombatInterface>( GetAvatarActorFromActorInfo()))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
		//TODO: Set the Projectile rotation
		AAuraProjectile* Projectile =GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//TODO: Give the projectile a gameplay effect to make damage
		Projectile->FinishSpawning(SpawnTransform);
		
	}
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UKismetSystemLibrary::PrintString(this, FString("Activated Ability(C++)"),true, true, FLinearColor::Green);
	// checkf(ProjectileClass,TEXT("ProjectileClass must be a valid ProjectileClass"));
	// bool bIsServer = HasAuthority(&ActivationInfo);
	// if (!bIsServer) return;
	// if (ICombatInterface* CombatInterface =Cast<ICombatInterface>( GetAvatarActorFromActorInfo()))
	// {
	// 	FTransform SpawnTransform;
	// 	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	// 	//TODO: Set the Projectile rotation
	// 	AAuraProjectile* Projectile =GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	// 	//TODO: Give the projectile a gameplay effect to make damage
	// 	Projectile->FinishSpawning(SpawnTransform);
	// 	
	// }
}
