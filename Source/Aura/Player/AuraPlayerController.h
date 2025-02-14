// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
class UAbilityInputTagDataAsset;
class IEnemyInterface;
class UInputMappingContext;
class UInputAction;
class USplineComponent;
struct FInputActionValue;


UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	
	void HandleMove(const FInputActionValue& InputValue);
	void HandleMoveToClick();
	void HandleNavigateToDestination();
	void StartSprint();
	void StopSprint();
	bool bIsSprinting = false;

	void AbilityInputTagPressed(FGameplayTag Tag);
	void AbilityInputTagReleased(FGameplayTag Tag);
	void AbilityInputTagHeld(FGameplayTag Tag);
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	// virtual void OnPossess(APawn* InPawn) override;
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void TraceCursor();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Setup|Ability")
	TObjectPtr<UAbilityInputTagDataAsset> AbilityInputTagDataAsset;

private:
	UAuraAbilitySystemComponent* GetAbilitySystemComponent();
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	/*
	 * Move to click properties
	 */
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
	//a bool to indicate whether we are clicking over something or not
	bool bTargeting = false;
	/*End MoveToClick Action*/
	
	void AutoRun();
	FHitResult CursorHit;
};
