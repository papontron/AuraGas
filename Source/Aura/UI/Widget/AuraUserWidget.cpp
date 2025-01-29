// Fill out your copyright notice in the Description page of Project Settings.


#include "Aura/UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	ReceiveSetWidgetController();
}
