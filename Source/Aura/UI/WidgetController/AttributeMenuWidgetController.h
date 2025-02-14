// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeSet.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayTag;
struct FAuraAttributeInfo;
class UAuraAttributeInfoDataAsset;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature,const FAuraAttributeInfo&, AttributeInfo);

/**
 * 
 */
//blueprintable = enables this class to be derived in blueprints, BlueprintType this class can be called in the event graph of any blueprint
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	
	virtual void BroadcastValues() override;
	
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly, Category="Delegate")
	FAttributeInfoSignature AttributeInfoDelegate;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	TObjectPtr<UAuraAttributeInfoDataAsset> PrimaryAttributeInfoDataAsset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	TObjectPtr<UAuraAttributeInfoDataAsset> SecondaryAttributeInfoDataAsset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	TObjectPtr<UAuraAttributeInfoDataAsset> DerivedAttributeInfoDataAsset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	TObjectPtr<UAuraAttributeInfoDataAsset> VitalAttributeInfoDataAsset;

	
private:
	void BroadCastAttributeInfo(const FGameplayTag &Tag, const FGameplayAttribute& Attribute, UAuraAttributeInfoDataAsset *DataAsset) const;
};
