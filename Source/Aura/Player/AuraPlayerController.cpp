// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Aura/Character/AuraCharacter.h"
#include "Aura/Interactive/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(AuraContext,TEXT("No AuraContext"));
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) // in multiplayer scenarios, the subsystem is valid only once, for the locally controlled player, for the rest, the subsystem doesnt have a valid LocalPlayer
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (MoveAction)
	{
		EnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,this, &AAuraPlayerController::HandleMove);	
	}
	if (MoveToClickAction)
	{
		EnhancedInput->BindAction(MoveToClickAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::HandleMoveToClick);
		
	}
	if (SprintAction)
	{
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Started,this,&AAuraPlayerController::StartSprint);
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Completed,this, &AAuraPlayerController::StopSprint );
	}
}

void AAuraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceCursor();
}

/*void AAuraPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	checkf(AuraPlayerState,TEXT("No AuraPlayerState"));
	
	AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(InPawn);
	
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState,AuraCharacter);
	AuraCharacter->SetAbilitySystemComponent(AuraPlayerState->GetAbilitySystemComponent());
	AuraCharacter->SetAttributeSet(AuraPlayerState->GetAttributeSet());
	
	
}*/


void AAuraPlayerController::HandleMove(const FInputActionValue& InputValue)
{
	FVector2D InputAxisVector = InputValue.Get<FVector2D>();
	const FRotator Rotator(0.f,GetControlRotation().Yaw,0.f);
	const FVector Forward = FRotationMatrix(Rotator).GetUnitAxis(EAxis::Y);
	const FVector Right = FRotationMatrix(Rotator).GetUnitAxis(EAxis::X);

	GetCharacter()->AddMovementInput(Forward, InputAxisVector.Y);
	GetCharacter()->AddMovementInput(Right, InputAxisVector.X);
	
	
}

void AAuraPlayerController::HandleMoveToClick()
{
	AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(GetPawn());
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility,true,HitResult);
	if (!HitResult.bBlockingHit) return;
	
	FVector ImpactPoint = HitResult.ImpactPoint;
	FVector ActorLocation = AuraCharacter->GetActorLocation();
	FVector Direction = (ImpactPoint - ActorLocation).GetSafeNormal();
	// FRotator Rotation = (ImpactPoint-ActorLocation).Rotation();
	FVector Forward(0.f,1.f,0.f);
	FVector Right(1.f,0.f,0.f);
	
	/*
	AuraCharacter->SetActorRotation((ImpactPoint-ActorLocation).Rotation());
	AuraCharacter->GetCharacterMovement()->Velocity = Direction*AuraCharacter->GetCharacterMovement()->MaxWalkSpeed;
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Magenta,FString::Printf(TEXT("Current velocity: %f"),AuraCharacter->GetCharacterMovement()->Velocity.Length()));*/

	AuraCharacter->AddMovementInput(Forward,Direction.Y);
	AuraCharacter->AddMovementInput(Right,Direction.X);
}

void AAuraPlayerController::StartSprint()
{
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 750.f;
}

void AAuraPlayerController::StopSprint()
{
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 320.f;
}

void AAuraPlayerController::TraceCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility,true,HitResult);
	if (!HitResult.bBlockingHit) return;
	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();
	/*Case 1:
	 *ThisActor exists and lastActor = nullptr:
	 *	HighLight thisActor
	 *Case 2:
	 *ThisActor exists and lastActor also exists but hey are different:
	 *HighLight thisActor and Unhighlight lastActor
	 *case 3:
	 *ThisActor exists and last actor also exists and both are the same: do nothing
	 *case 4:
	 *thisActor doesnt exist and last actor doesnt exit neither:
	 *Do nothing
	 *case 5:
	 *ThisActor doesnt exist and last actor existed:
	 *Unhighlight lastActor
	*/
	if (ThisActor != nullptr)
	{
		//case1:
		if (LastActor == nullptr)
		{
			ThisActor->bIsHighlighted = true;
			ThisActor->HighlightUnhighlight();
		}else
		{
			if (ThisActor!=LastActor)
			{
				LastActor->bIsHighlighted = false;
				LastActor->HighlightUnhighlight();
				ThisActor->bIsHighlighted = true;
				ThisActor->HighlightUnhighlight();
			}
		}
	}else
	{
		if (LastActor != nullptr)
		{
			LastActor->bIsHighlighted = false;
			LastActor->HighlightUnhighlight();
		}
	}
}