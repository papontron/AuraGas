// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"

#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Character/AuraCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(ASCInterface->GetAbilitySystemComponent());
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AuraAbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		float CurrentHealth = AuraAttributeSet->GetHealth();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health = %f"), CurrentHealth));
		const_cast<UAuraAttributeSet*>(AuraAttributeSet)->SetHealth(50.f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health = %f"), AuraAttributeSet->GetHealth()));
		Destroy();
	}
	
}


