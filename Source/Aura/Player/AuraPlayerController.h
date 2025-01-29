// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
/**
 * 
 */
class UInputMappingContext;
class UInputAction;
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
	TObjectPtr<UInputAction> MoveToClickAction;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	
	void HandleMove(const FInputActionValue& InputValue);
	void HandleMoveToClick();
	void StartSprint();
	void StopSprint();
	bool bIsSprinting = false;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	// virtual void OnPossess(APawn* InPawn) override;
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void TraceCursor();
};
