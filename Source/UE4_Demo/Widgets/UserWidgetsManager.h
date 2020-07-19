// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserWidgetPanel.h"
#include "EnumAsByte.h"
#include "UserWidgetsManager.generated.h"

class UUserWidgetPanel;
/**
 * 
 */
UCLASS()
class UE4_DEMO_API UUserWidgetsManager : public UObject
{
	GENERATED_BODY()
	
private:
	TMap<FName, UUserWidgetPanel*> m_widgets;

public:
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void showWidget(const FName& path, uint8 showType, const FName& associatedName, bool create = true);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void hideWidget(const FName& path, uint8 hideType);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void removeWidget(const FName& path);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	UUserWidgetPanel* findWidget(const FName& path);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	int32 findWidgets(int32 catalog, TArray<UUserWidgetPanel*>& widgets);
};
