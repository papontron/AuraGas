// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemLibrary.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Aura/UI/WidgetController/AuraWidgetController.h"
#include "Kismet/GameplayStatics.h"

const UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldObjectContext)
{
	APlayerController* PlayerController = WorldObjectContext->GetWorld()->GetFirstPlayerController();
	checkf(PlayerController ,TEXT("Player controller is null at: AuraAbilitySystemComponentLibrary"));
	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD());
	checkf(AuraHUD,TEXT("HUD is null at: AuraAbilitySystemComponentLibrary"));
	
	FWidgetControllerParams Params;
	Params.PlayerController =WorldObjectContext->GetWorld()->GetFirstPlayerController();
	Params.PlayerState = Params.PlayerController->GetPlayerState<AAuraPlayerState>();
	Params.AbilitySystemComponent  = Params.PlayerController->GetPlayerState<AAuraPlayerState>()->GetAbilitySystemComponent();
	Params.AttributeSet = Params.PlayerController->GetPlayerState<AAuraPlayerState>()->GetAttributeSet();
	
	return AuraHUD->GetOverlayWidgetController(Params);
}

const UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	checkf(PlayerController,TEXT("Player controller is null at: AuraAbilitySystemLibrary"));
	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD());
	checkf(AuraHUD,TEXT("HUD is null at: AuraAbilitySystemLibrary"));
	FWidgetControllerParams Params;
	Params.PlayerController = PlayerController;
	Params.PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
	Params.AbilitySystemComponent = Params.PlayerController->GetPlayerState<AAuraPlayerState>()->GetAbilitySystemComponent();
	Params.AttributeSet = Params.PlayerController->GetPlayerState<AAuraPlayerState>()->GetAttributeSet();
	return AuraHUD->GetAttributeMenuWidgetController(Params);
}
