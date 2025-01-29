// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEnemy.h"

#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AAuraEnemy::AAuraEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GetCapsuleComponent()->SetCapsuleHalfHeight(54.f);
	FTransform MeshTransform;
	MeshTransform.SetLocation(FVector(0, 0, -50));
	MeshTransform.SetRotation(FQuat(FRotator(0, -90, 0)));
	GetMesh()->SetWorldTransform(MeshTransform);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	//gameplay ability system
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystem_Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

// Called when the game starts or when spawned
void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

// Called every frame
void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAuraEnemy::HighlightUnhighlight()
{
	if (bIsHighlighted)
	{
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(255);
		
	}else
	{
		GetMesh()->SetRenderCustomDepth(false);
		GetMesh()->SetCustomDepthStencilValue(0);
	}
}






