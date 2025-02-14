// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}


USkeletalMeshComponent* AAuraCharacterBase::GetWeapon()
{
	return Weapon;
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::SetAbilitySystemComponent(UAbilitySystemComponent* InAbilitySystemComponent)
{
	AbilitySystemComponent = InAbilitySystemComponent;
}

void AAuraCharacterBase::SetAttributeSet(UAttributeSet* InAttributeSet)
{
	AttributeSet = InAttributeSet;
}

void AAuraCharacterBase::InitAllAttributes() const
{
	InitPrimaryAttributes();
	InitSecondaryAttributes();
	InitVitalAttributes();
}

void AAuraCharacterBase::InitPrimaryAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.f);
}

void AAuraCharacterBase::InitSecondaryAttributes() const
{
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.f);
}

void AAuraCharacterBase::InitVitalAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributes,1.f);
}

void AAuraCharacterBase::GrantStartUpAbilities() const
{
	if (!HasAuthority()) return;
	CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent)->GrantAbilities(StartUpAbilities);
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> &GameplayEffectClass,const float ActorLevel) const
{
	checkf(IsValid(GetAbilitySystemComponent()), TEXT("Ability System component isn't valid"));
	checkf(GameplayEffectClass, TEXT("DefaultPrimaryAttributes GameplayEffect must not be NULL"));
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}


FVector AAuraCharacterBase::GetCombatSocketLocation() const
{
	checkf(Weapon, TEXT("This character doesn't have a weapon"))
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}