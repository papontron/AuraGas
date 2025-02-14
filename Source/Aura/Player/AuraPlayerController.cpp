// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Aura/Input/AuraInputComponent.h"
#include "Aura/Interactive/EnemyInterface.h"
#include "Components/SplineComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
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
	checkf(AbilityInputTagDataAsset,TEXT("AbilityInputTagDataAsset is nullptr") );
	UAuraInputComponent* AuraEnhancedInput = Cast<UAuraInputComponent>(InputComponent);
	if (MoveAction)
	{
		AuraEnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,this, &AAuraPlayerController::HandleMove);	
	}
	if (SprintAction)
	{
		AuraEnhancedInput->BindAction(SprintAction,ETriggerEvent::Started,this,&AAuraPlayerController::StartSprint);
		AuraEnhancedInput->BindAction(SprintAction,ETriggerEvent::Completed,this, &AAuraPlayerController::StopSprint );
	}
	//Bind actions to the ability input actions from the data asset
	AuraEnhancedInput->BindInputAbilityActions(AbilityInputTagDataAsset,this,&ThisClass::AbilityInputTagPressed,&AAuraPlayerController::AbilityInputTagReleased,&AAuraPlayerController::AbilityInputTagHeld);
}

void AAuraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceCursor();
	AutoRun();
}


void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		const float DistanceToDestination = (LocationOnSpline-CachedDestination).Length();
		if (DistanceToDestination<=AutoRunAcceptanceRadius)
		{	
			bAutoRunning = false;
		}
	}
}



void AAuraPlayerController::HandleMove(const FInputActionValue& InputValue)
{
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();
	const FRotator Rotator(0.f,GetControlRotation().Yaw,0.f);
	const FVector Forward = FRotationMatrix(Rotator).GetUnitAxis(EAxis::Y);
	const FVector Right = FRotationMatrix(Rotator).GetUnitAxis(EAxis::X);
	GetCharacter()->AddMovementInput(Forward, InputAxisVector.Y);
	GetCharacter()->AddMovementInput(Right, InputAxisVector.X);
}

void AAuraPlayerController::HandleMoveToClick()
{
	//this requires the right mouse button to be pressed to get the actor moved to the destination(bit by bit)
	FollowTime += GetWorld()->GetDeltaSeconds();
	APawn* ControlledPawn = GetPawn();
	if (CursorHit.bBlockingHit)
	{
		CachedDestination = CursorHit.ImpactPoint;
		const FVector Direction = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(Direction);
	}
}

void AAuraPlayerController::HandleNavigateToDestination()
{
	//dont forgot to check Allow client navigation in the project settings / navigation system
	if (APawn* ControlledPawn = GetPawn())
	{
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlledPawn->GetActorLocation(),CachedDestination);
		SplineComponent->ClearSplinePoints();
		for (FVector &VectorPoint: NavPath->PathPoints)
		{
			SplineComponent->AddSplinePoint(VectorPoint,ESplineCoordinateSpace::World);
			DrawDebugSphere(GetWorld(),VectorPoint,10.f, 16,FColor::Emerald,false,5.f);
		}
		
		//switched the destination to the last point of the spline, so that it can be reachable
		CachedDestination = NavPath->PathPoints.Last();
		//this will trigger the auto run in the event tick
		bAutoRunning = true;
	}
}

void AAuraPlayerController::StartSprint()
{
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 750.f;
}

void AAuraPlayerController::StopSprint()
{
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 320.f;
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag Tag)
{
	if (!GetAbilitySystemComponent()) return;
	if (Tag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
	{
		bTargeting = ThisActor?true:false;
		//always reset auto running when an ability input is pressed 
		bAutoRunning = false;
	}
	//GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,FString::Printf(TEXT("Ability Tag Pressed:%s"),*Tag.ToString()));
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag Tag)
{
	if (!GetAbilitySystemComponent()) return;
	if (!Tag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
	{
		GetAbilitySystemComponent()->AbilityInputTagReleased(Tag);
		return;
	}
	if (bTargeting)
	{
		//if there is a target under the cursor hit, then release the ability
		GetAbilitySystemComponent()->AbilityInputTagReleased(Tag);
	}else
	{
		if (FollowTime<=ShortPressThreshold)
		{
			HandleNavigateToDestination();
		}
		FollowTime = 0;
		bTargeting = false;
	}
	//GEngine->AddOnScreenDebugMessage(2,5.f,FColor::Blue,FString::Printf(TEXT("Ability Tag Released:%s"),*Tag.ToString()));
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag Tag)
{
	if (!GetAbilitySystemComponent()) return;
	
	if (!Tag.MatchesTagExact(FAuraGameplayTags::Get().Input_Ability_RMB))
	{
		GetAbilitySystemComponent()->AbilityInputTagHeld(Tag);
		return;
	}
	if (bTargeting)
	{
		//if there is a target under the cursor hit
		GetAbilitySystemComponent()->AbilityInputTagHeld(Tag);
	}else
	{
		//MoveToClick behavior
		HandleMoveToClick();
	}
	//GEngine->AddOnScreenDebugMessage(3,5.f,FColor::Green,FString::Printf(TEXT("Ability Tag Held:%s"),*Tag.ToString()));
}

void AAuraPlayerController::TraceCursor()
{
	
	GetHitResultUnderCursor(ECC_Visibility,true,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
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

UAuraAbilitySystemComponent* AAuraPlayerController::GetAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
