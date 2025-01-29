﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura/Player/AuraPlayerController.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Aura/UI/Widget/AuraUserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAuraCharacter::AAuraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	UCharacterMovementComponent* AuraMovementComponent = GetCharacterMovement();
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	AuraMovementComponent->bOrientRotationToMovement = true;
	AuraMovementComponent->RotationRate = FRotator(0, 500.f, 0);
	AuraMovementComponent->bConstrainToPlane = true;
	AuraMovementComponent->bSnapToPlaneAtStart = true;
	AuraMovementComponent->MaxWalkSpeed = 320.f;
	
	//Camera and spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 750.f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	FTransform SpringArmTransform;
	SpringArmTransform.SetRotation(FQuat(FRotator(-45.f,0,0.f)));
	SpringArm->SetWorldTransform(SpringArmTransform);
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bUsePawnControlRotation = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(SpringArm);

	
	
	
	FTransform MeshTransform;
	MeshTransform.SetLocation(FVector(0,0,-80.f));
	MeshTransform.SetRotation(FQuat(FRotator(0, -90.f, 0.f)));
	GetMesh()->SetWorldTransform(MeshTransform);
}


void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeActorInfo();
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		//since the player controller is only valid for the locally controlled pawn(multiplayer game)
		AAuraPlayerState* AuraPlayerState = AuraPlayerController->GetPlayerState<AAuraPlayerState>();
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))//the hud is only valid for the locally controlled player, not for the other remote controlled players in the multiplayer game
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
			
		}

	}
	
}



void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitializeActorInfo();
}


void AAuraCharacter::InitializeActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	checkf(AuraPlayerState,TEXT("Player state is null"));
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
}