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
	TMap<FString, UUserWidgetPanel*> m_widgets;

public:
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	UUserWidgetPanel* createWidget(const FString& path);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void showWidget(const FString& path, uint8 showType, const FString& associatedName, bool create = true);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void hideWidget(const FString& path, uint8 hideType);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	bool addWidget(const FString& path, UUserWidgetPanel* pWidgetPanel);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	void removeWidget(const FString& path);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	UUserWidgetPanel* findWidget(const FString& path);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	int32 findWidgets(int32 catalog, TArray<UUserWidgetPanel*>& widgets);
};
